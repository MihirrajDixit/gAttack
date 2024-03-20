#include <uhd.h>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/types/stream_cmd.hpp>
#include <complex>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>

// How to run this
// g++ -std=c++11 -I/usr/local/include -L/usr/local/lib new_sample.cpp -luhd  -o new_sample 
// g++ -std=c++11 -I/usr/local/include -L/usr/local/lib dl_sample.cpp -luhd  -o dl_sample && g++ -std=c++11 -I/usr/local/include -L/usr/local/lib ul_sample.cpp -luhd  -o ul_sample

int main() {
    auto usrp = uhd::usrp::multi_usrp::make("type=x300,serial=323D0F6,clock=external");
    // uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make();
    size_t duration = 1;  //number of seconds (in 10 seconds slot)
    size_t num_samps = 1; // number of samples received
    double dl_freq = 2680e6; // Hz
    // double ul_freq = 2560e6; // Hz
    double sample_rate = 23040000; // Hz
    double gain = 50; // dB

    usrp->set_rx_rate(sample_rate, 0);
    usrp->set_rx_freq(dl_freq, 0);
    usrp->set_rx_gain(gain, 0);
    usrp->set_clock_source("external");
    usrp->set_time_source("external");
    usrp->get_time_synchronized();

    uhd::stream_args_t st_args("fc32", "sc16");
    st_args.channels = {0};

    uhd::rx_metadata_t metadata;
    uhd::rx_streamer::sptr streamer = usrp->get_rx_stream(st_args);
    std::vector<std::complex<float>> recv_buffer(230400000);

    // Start Stream
    uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
    stream_cmd.stream_now = true;

    // Wait for 1 PPS to happen, then set the time at next PPS to 0.0
    double time_at_last_pps = usrp->get_time_last_pps().get_real_secs();
    while (time_at_last_pps == usrp->get_time_last_pps().get_real_secs()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // keep waiting till it happens- if this while loop never finishes then the PPS signal isn't there
    }
    usrp->set_time_next_pps(uhd::time_spec_t(0.0));
    uhd::time_spec_t cmdTime = usrp->get_time_now() + uhd::time_spec_t(1.0);
    usrp->set_command_time(cmdTime);
    // issue stream cmd
    streamer->issue_stream_cmd(stream_cmd);

    // Receive Samples
    
    std::cout << "started" << std::endl;
    for (size_t i = 0; i < duration*num_samps; ++i) {
        std::cout << std::chrono::high_resolution_clock::now().time_since_epoch().count() << ",dl 1" << std::endl;
        streamer->recv(&recv_buffer.front(), recv_buffer.size(), metadata);
        // std::cout << std::chrono::high_resolution_clock::now().time_since_epoch().count() << ", 2" << std::endl;
        std::ofstream ofs("/media/anonymous/Work + Games/signal_data/dl_samples_" + std::to_string(i) + ".txt", std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(&recv_buffer.front()), recv_buffer.size()*sizeof(std::complex<float>));
        std::cout << std::chrono::high_resolution_clock::now().time_since_epoch().count() << ",dl 3" << std::endl;
    }

    // Stop Stream
    stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
    streamer->issue_stream_cmd(stream_cmd);
    return 0;
}
