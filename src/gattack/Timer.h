#pragma once

#include <chrono>
// NB: ALL OF THESE 3 FUNCTIONS BELOW USE SIGNED VALUES INTERNALLY AND WILL
// EVENTUALLY OVERFLOW (AFTER 200+ YEARS OR SO), AFTER WHICH POINT THEY WILL
// HAVE *SIGNED OVERFLOW*, WHICH IS UNDEFINED BEHAVIOR (IE: A BUG) FOR C/C++.
// But...that's ok...this "bug" is designed into the C++11 specification, so
// whatever. Your machine won't run for 200 years anyway...

// Get time stamp in milliseconds.
//code from https://stackoverflow.com/a/49066369

class Timer {
public:
    Timer(){};
    uint64_t xyz;
    uint64_t millis();
    // Get time stamp in microseconds.
    uint64_t micros();
    // Get time stamp in nanoseconds.
    static uint64_t nanos();
    // uint64_t ul_rach_time;
    // uint64_t dl_rar_time;
private:

};

