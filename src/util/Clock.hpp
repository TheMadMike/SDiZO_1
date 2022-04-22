// Copyright 2022 by Michał Gibas
#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

namespace sdizo {


/* Utility class for easy time measuring */
class Clock {

public:
    Clock();
    
    void start();
    void stop();

    /* get measured time in milliseconds*/
    double getDurationMs();
    /* get measured time in microseconds*/
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