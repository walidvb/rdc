/*---------------------------------------------------------------
 
 Creation:	17.11.2012
 Description:		A fake camera, working with Cinder, returning the exact image that was produced.
 Methodes:			Construct/Destruct
                    init()
                    grabFrame()
                    grabFrameTest()
 ---------------------------------------------------------------*/

#ifndef RDC_Camera_h
#define RDC_Camera_h

#include "Sensor_A.h"
#include "cinder/Channel.h"
#include "cinder/ImageIo.h"

using namespace ci;

class SensorSim : public Sensor_A
{
public:
    SensorSim();
    SensorSim(int width, int height);
    void init();
    Image grabFrame();      //return the frame captured by the camera
    Image grabFrameTest();  //returns the exact image that was projected(not captured by a camera, so mapping will be 1:1)
    
    Image chan2floats(Channel32f channel);

    int getFrameCount() const;
    
    
private:
    Channel32f loadFakeFrame();
    int frameCount;
};

#endif
