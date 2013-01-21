//
//  RDC.h
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#ifndef RDC_RDC_h
#define RDC_RDC_h
#include "common.h"
class Sensor;
class Renderer_A;
class RDC
{
public:
    RDC(){}
    void calibrate(Sensor* cam, Renderer_A* gfx);   //Called once, starts the calibration and computes needed values for compensation
    Image compensate(const Image& srcImg); //Called each frame, takes source image and returns compensated image
    
private:
    //Private methods
    int getLatency(); //get projector camera latency
    void projectStructuredLights(Renderer_A* gfx);//will call gfx->drawRect, etc...
    
    void computeEM(); //compute the environment light
    void computeFM(); // compute the max projected light
    
    vector<float> camera2proj; //Camera to projector mapping
    vector<float> EM; //Texture storing the environmental light, row major
    vector<float> FM; //Texture storing the proj light, row major
};

#endif
