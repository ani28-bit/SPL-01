#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    bool running;

public:
    Timer();
    
    // Start the timer
    void start();
    
    // Stop the timer
    void stop();
    
    // Get elapsed time in seconds
    double getElapsedSeconds() const;
    
    // Get elapsed time in milliseconds
    double getElapsedMilliseconds() const;
    
    // Reset the timer
    void reset();
};

#endif