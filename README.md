
# gAttack - 

**gAttack** 

Attack module for overshadowing, wrapped around LTESniffer, based on Kaist group.


gAttack

Usage: gAttack [aAcCDdEfghHilLnpPrRsStTvwWyYqFIuUmOoz] -f rx_frequency (in Hz) | -i input_file
	-h show this help message
	-a RF args [Default ]
	-g RF fix RX gain [Default AGC]
	-M Interface 1-ZMQ/2-RF
	-b Attack Mode [1 - RACH TA]
	-B RF Tx Gain [Default 0.0
	-i input_file [Default use RF board] (default disable)
	-D output filename for DCI [default stdout]
	-o offset frequency correction (in Hz) for input file [Default 0.0 Hz]
	-O offset samples for input file [Default 0]
	-P nof_ports for input file [Default 2]
	-c cell_id for input file [Default 0]
	-C Enable cell search, default disable, 
	-C Disable CFO correction [Default Enabled]
	-t Add time offset [Default 0]
	-y set the cpu affinity mask [Default -1]
	-Y set the decimate value [Default 0]
	-W Number of concurent threads [2..W, Default 4]
	-s skip decoding of secondary (less frequent) DCI formats
	-S split ratio for primary/secondary DCI formats [0.0..1.0, Default 0.990000]
	-T interval to perform dci format split [Default 500 ms]
	-v [set srsran_verbose to debug, default none]
	-q Enable MCS table tracking algorithm (Default best: enable)
	-r Target RNTI, LTESniffer only decodes traffic of input target RNTI 
	-I Specify a cell ID, need to remove -C to use this option (Default disable)
	-p Specify number of PRB of specified cell ID (-I) (Default 50)
	-f Downlink Frequency
	-u Uplink Frequency  
	-A Number of RX antennas [Default 1]
	-m Sniffer mode, 0 for downlink sniffing mode, 1 for uplink sniffing mode
	-z API mode, 0 for identity mapping, 1 for IMSI collecting, 2 for UECapability profiling, 3 for all
	-d Enable debug mode, print debug message to screen (Defautl disable)



Usage:
gAttack -M 2 -a "type=x300,serial=323D0F6" -A 2 -W 4 -C -f 1845e6 -u 1750e6 -m 1 -z 3
