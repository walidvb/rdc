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

#define SCALESCOUNT 10
namespace www {class Timer;}
class Homo;
class Sensor;
class Renderer_A;

struct colorMapping{
    double src;
    double cap;
};

enum Colors {RED, GREEN, BLUE};

class ColorCalibrator{
public:
    ColorCalibrator();
    ColorCalibrator(Homo* homo, www::Timer* timer);
    ~ColorCalibrator(){};
    
    void calibrate(Sensor* sensor, Renderer_A* gfx);
    void calibrateColor(Colors color, Sensor* sensor, Renderer_A* gfx);
    void computeResponse(Colors color, Image* capture);
    
    
    //Getters&Setters
    bool getIsCalibrated();
private:
    //Private methods
    double getCol(int index, Colors color, Image* img);
    
    //Ext attr
    www::Timer* timer;
    Homo* homo;
    bool isCalibrated;
    
    //Int attr
    string resources;
    std::vector<bool> colorDone;
    int timeToWait;
    int squareSize;
    
    int colorMap[3][SCALESCOUNT];
};



#endif
