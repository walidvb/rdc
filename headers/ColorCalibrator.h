//
//  ColorCalibrator.h
//  RDC
//
//  Created by Gaston on 3/18/13.
//
//

#ifndef RDC_ColorCalibrator_h
#define RDC_ColorCalibrator_h


#include "common.h"
#include "Controller.h"
#include "Sensor.h"
#include "Renderer_Cinder.h"
#include "Renderer_CV.h"
#include "Timer.h"

class Timer;
class Homo;
class Sensor;
class Renderer_A;

struct colorMapping{
    double src;
    double cap;
} ;

class ColorCalibrator{
public:
    ColorCalibrator();
    ColorCalibrator(Sensor* sensor, Homo* homo, Renderer_A* renderer, Timer* timer);
    ~ColorCalibrator(){};
    
    void calibrate();
    
private:
    //
    
    //Attributes
    Timer* timer;
    Renderer_A* renderer;
    Homo* homo;
    Sensor* sensor;

    std::vector<colorMapping> gammaLevels;
    std::vector<colorMapping> redLevels;
    std::vector<colorMapping> greenLevels;
    std::vector<colorMapping> blueLevels;
};



#endif
