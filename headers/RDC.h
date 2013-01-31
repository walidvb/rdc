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
    void calibrate(Sensor* cam, Renderer_A* gfx);       //<!Called once, starts the calibration and computes needed values for compensation
    Image compensate(Image& srcImg, Image& dstImage);   //<!Called each frame, takes source image and returns compensated image
private:
    //Private methods
    int getLatency(); //<! get projector camera latency
    void projectStructuredLights(Renderer_A* gfx);//<! will call gfx->drawRect, or simply gfx->drawImg
    void computeHomography();

    void computeEM(); //<! compute the environment light
    void computeFM(); //<! compute the max projected light
    
    vector<float> camera2proj; //<! Camera to projector mapping
    Mat EM; //<! Matrix storing the environmental light, row major
    Mat FM; //<! Matrix storing the proj light, row major
};

#endif
