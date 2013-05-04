//
//  Timer.cpp
//  RDC
//
//  Created by Gaston on 3/18/13.
//
//

#include <stdio.h>
#include "Timer.h"
using namespace www;

Timer::Timer()
{
    time(&timeZero);
    time(&lastLap);
}

void Timer::resetTimer()
{
    time(&lastLap);
}

bool Timer::hasElapsed(double Xs)
{
    bool hasElapsed = (difftime(time(NULL), lastLap) >= Xs);
    return hasElapsed;
}

double Timer::hasElapsed()
{
    double timeElapsed = difftime(time(NULL),lastLap);
    return timeElapsed;
}

double Timer::totalTime()
{
    return difftime(time(NULL),timeZero);
}