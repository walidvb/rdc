//
//  Timer.h
//  RDC
//
//  Created by Gaston on 3/18/13.
//
//

#ifndef RDC_Timer_h
#define RDC_Timer_h
#include <time.h>

class Timer{

public:
    Timer();
    ~Timer(){};
    
    //timer logic
    void resetTimer();                  //<! resets timer to 0
    bool hasElapsed(double Xs);           //<! checks if Xms has elapsed since last reset
    double hasElapsed();                   //<! returns time elapsed since lastLap
    double totalTime();
    
private:
    time_t timeZero;                    //<! a simple timer
    time_t lastLap;                     //<! last time the lap
};
#endif