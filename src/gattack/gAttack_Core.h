/*
 * Copyright (c) 2019 Robert Falkenberg.
 *
 * This file is part of FALCON 
 * (see https://github.com/falkenber9/falcon).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 */
#pragma once

#include <map>

#include "ArgManager.h"
#include "falcon/common/SignalManager.h"
#include "gattack/SubframeWorker.h"
#include "gattack/ThreadSafeQueue.h"
#include "gattack/WorkerThread.h"
#include "Sniffer_dependency.h"
#include "MCSTracking.h"
#include "ULSchedule.h"
#include "srsran/common/mac_pcap.h"
#include "Phy.h"
#include "PcapWriter.h"
#include "Timer.h"
#include "HARQ.h"
#include <ctime>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>
#include "srsue/hdr/ue.h"
#include "falcon/prof/Lifetime.h"

using namespace srsue;
namespace bpo = boost::program_options;

// include C-only headers
#ifdef __cplusplus
    extern "C" {
#endif

#include "srsran/phy/utils/debug.h"
#include "falcon/phy/falcon_ue/falcon_ue_dl.h"
#include "srsran/srsran.h"
#include "srsran/phy/rf/rf.h"
#include "srsran/phy/rf/rf_utils.h"

#ifdef __cplusplus
}
#undef I // Fix complex.h #define I nastiness when using C++
#endif
using namespace srsran;

#define UL_SNIFFER_UL_MAX_OFFSET 200
#define UL_SNIFFER_UL_OFFSET_32 32
#define UL_SNIFFER_UL_OFFSET_64 64

typedef struct {
  cf_t* ta_temp_buffer;
  cf_t  ta_last_sample[UL_SNIFFER_UL_MAX_OFFSET];
  int   cnt =  0;
  int   sf_sample_size;

} UL_Sniffer_ta_buffer_t;

static SRSRAN_AGC_CALLBACK(srsran_rf_set_rx_gain_th_wrapper_)
{
  srsran_rf_set_rx_gain_th((srsran_rf_t*)h, gain_db);
}

int srsran_rf_recv_wrapper( void* h,
                            cf_t* data_[SRSRAN_MAX_PORTS], 
                            uint32_t nsamples, 
                            srsran_timestamp_t* t);

class gAttack_Core : public SignalHandler {
public:
  gAttack_Core(const Args& args);
  gAttack_Core(const gAttack_Core&) = delete; //prevent copy
  gAttack_Core& operator=(const gAttack_Core&) = delete; //prevent copy
  virtual ~gAttack_Core() override;
  
  RNTIManager &getRNTIManager();
  void setDCIConsumer(std::shared_ptr<SubframeInfoConsumer> consumer);
  void resetDCIConsumer();
  void refreshShortcutDiscovery(bool val);
  void setRNTIThreshold(int val);
  void print_api_header();
  bool run();
  void stop();
  
  // Timer* ltetimer = new Timer();
private:

  void handleSignal() override;

  Args                    args;
  int                     nof_workers;
  int                     sniffer_mode;     //-m
  int                     api_mode    ;     // -z
  bool                    go_exit = false;
  enum receiver_state     { DECODE_MIB, DECODE_PDSCH} state;
  std::mutex              harq_map_mutex;
  Phy                     *phy;
  gAttack_pcap_writer  pcapwriter;
  Timer                 ltetimer;
  srsran::mac_pcap        mac_pcap;
  int                     mcs_tracking_mode;
  MCSTracking             mcs_tracking;
  ULSchedule              ulsche;
  UL_Sniffer_ta_buffer_t  ta_buffer;
  std::atomic<float>      est_cfo; //cfo from chest in subframe workers
  UL_HARQ                 ul_harq; // test UL_HARQ
  HARQ                    harq; // test HARQ function
  int                     harq_mode;
};
