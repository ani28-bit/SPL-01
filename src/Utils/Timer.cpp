#include "Timer.h"

Timer::Timer() : running(false) {}

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
    running = false;
}

double Timer::getElapsedSeconds() const {
    std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint;
    
    if (running) {
        endTimePoint = std::chrono::high_resolution_clock::now();
    } else {
        endTimePoint = endTime;
    }
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        endTimePoint - startTime
    );
    
    return duration.count() / 1000000.0;
}

double Timer::getElapsedMilliseconds() const {
    return getElapsedSeconds() * 1000.0;
}

void Timer::reset() {
    running = false;
}