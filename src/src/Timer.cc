#include "gattack/Timer.h"

// NB: ALL OF THESE 3 FUNCTIONS BELOW USE SIGNED VALUES INTERNALLY AND WILL
// EVENTUALLY OVERFLOW (AFTER 200+ YEARS OR SO), AFTER WHICH POINT THEY WILL
// HAVE *SIGNED OVERFLOW*, WHICH IS UNDEFINED BEHAVIOR (IE: A BUG) FOR C/C++.
// But...that's ok...this "bug" is designed into the C++11 specification, so
// whatever. Your machine won't run for 200 years anyway...

// code from https://stackoverflow.com/a/49066369


// uint64_t ul_rach_time = 0;
// uint64_t dl_rar_time = 0;
// Get time stamp in milliseconds.

uint64_t Timer::millis(){
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    return ms; 
};

// Get time stamp in microseconds.
uint64_t Timer::micros()
{
    uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    return us; 
}

// Get time stamp in nanoseconds.
uint64_t Timer::nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    return ns; 
}