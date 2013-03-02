//
//  Sensor.h
//  RDC
//
//  Created by Gaston on 1/21/13.
//
//

#ifndef RDC_Sensor_h
#define RDC_Sensor_h

#include "common.h"
#include "Image.h"

using namespace cv;

class Sensor
{
public:
    Sensor();
    Sensor(int width, int height);
    string init(string source);     //<! open a file
    int init(int deviceID);         //<! open a device
    Image grabFrame();              //<! grab a frame
    void destroy();                 //<! destroy the device
    bool isOpened();                  //<! returns true if a device/stream is open
    //Getters and Setters
    int getWidth() const;
    int getHeight() const;
    Size getSize() ;
    
private:
    VideoCapture cap;
    Image frame;
    int width;
    int height;
    int sensorType;
};


#endif
