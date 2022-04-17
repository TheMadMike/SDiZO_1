// Copyright 2022 by Michał Gibas
#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

namespace sdizo {

class Clock {

public:
    Clock();

    void start();
    void stop();

    double getDurationMs();
    double getDurationUs();

private:
    
    typedef std::chrono::high_resolution_clock HighResolutionClock;
    typedef std::chrono::time_point<HighResolutionClock> Timepoint;
    typedef std::chrono::duration<double, std::milli> DoubleMillisecondsDuration;
    typedef std::chrono::duration<double, std::micro> DoubleMicrosecondsDuration;

    Timepoint startPoint, stopPoint;
    HighResolutionClock internalClock;
};

};

#endif //CLOCK_HPP