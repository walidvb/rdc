//
//  SensorCaptor.h
//  RDC
//
//  Created by Gaston on 1/20/13.
//
//

#ifndef RDC_SensorCaptor_h
#define RDC_SensorCaptor_h

#include "common.h"
#include "Sensor_A.h"

using namespace cv;

class SensorCaptor : public Sensor_A
{
public:
    SensorCaptor();
    SensorCaptor(int width, int height);
    virtual void init() = 0;
    virtual Image grabFrame() = 0;

private:
    VideoCapture cap;
};

#endif
