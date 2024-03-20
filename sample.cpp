#include <iostream>
#include "uhd.h"
#include "uhd/usrp/multi_usrp.hpp"
// #include "uhd/types/metadata.h"
// using namespace uhd;

int main() {
  std::cout << "Hello World!\n";
  return 0;
}

void usrp_receiver(){
    
    auto usrp = uhd::usrp::multi_usrp::make("");
    // Configure the USRP here, incl. frequency, gain, etc.
    uhd::stream_args_t st_args("fc32", "sc16");
    auto rx_stream = usrp->get_rx_stream(st_args);
    uhd::rx_metadata_t md{};
    // Figure out the current time
    auto time_now = usrp->get_time_now();
    // Craft timed command
    uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
    stream_cmd.stream_now = false; // Enable timed streaming
    stream_cmd.time_spec = time_now + 1.0; // Start 1s in the future
    rx_stream->issue_stream_cmd(stream_cmd);
    // We assume buffers etc. have been allocated
    const double timeout = 2.0; // We need to wait at least 1 seconds before samples arrive
    num_recvd = rx_stream->recv(buffs, nsamps_per_buff, md, timeout);
    // The first sample in 'buffs' will be captured at the requested time. Also,
    // the metadata object (md) will most likely contain a timestamp which then will
    // match that in the stream command.
}