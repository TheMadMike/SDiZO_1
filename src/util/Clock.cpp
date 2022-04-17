// Copyright 2022 by Michał Gibas
#include "Clock.hpp"

namespace sdizo {

Clock::Clock() {
    internalClock = HighResolutionClock();
}

void Clock::start() {
    startPoint = internalClock.now();
}

void Clock::stop() {
    stopPoint = internalClock.now();
}

double Clock::getDurationMs() {
    DoubleMillisecondsDuration duration = stopPoint - startPoint;

    return duration.count();
}

double Clock::getDurationUs() {
    DoubleMicrosecondsDuration duration = stopPoint - startPoint;

    return duration.count();
}


};