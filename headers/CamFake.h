/*---------------------------------------------------------------
 
 Creation:	17.11.2012
 Description:		A fake camera, working with Cinder
 Methodes:			Construct/Destruct
 init()
 grabFrame()
 grabFrameTest()
 ---------------------------------------------------------------*/

#ifndef RDC_CamFake_h
#define RDC_CamFake_h

#include "Camera_A.h"
#include "cinder/Channel.h"
#include "cinder/ImageIo.h"

using namespace ci;

class CamFake : public Camera_A
{
public:
    CamFake();
    CamFake(int width, int height);
    void init();
    vector<float> grabFrame();      //return the frame captured by the camera
    
    int getFrameCount() const;
    
    
private:
    Channel32f fakeFrame = Channel32f( loadImage( loadUrl( "pattern/horizontal/i1.png" ) ) );
    int frameCount;
};

#endif
