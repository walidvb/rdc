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

#include "Camera_A.h"
#include "cinder/Channel.h"
#include "cinder/ImageIo.h"

using namespace ci;

class Cam : public Camera_A
{
public:
    Cam();
    Cam(int width, int height);
    void init();
    vector<float> grabFrame();      //return the frame captured by the camera
    vector<float> grabFrameTest();  //returns the exact image that was projected(not captured by a camera, so mapping will be 1:1)
    
    vector<float> chan2floats(Channel32f channel);

    int getFrameCount() const;
    
    
private:
    Channel32f loadFakeFrame();
    int frameCount;
};

#endif
