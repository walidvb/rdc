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
class Camera_A;
class RDC
{
public:
    RDC(Camera_A* cam);
    void calibrate();   //Called once, starts the calibration and computes needed values for compensation
    vector<float> compensate(const vector<float>& srcImg); //Called each frame, takes source image and returns compensated image
    
private:
    //Private methods
    int getLatency(); //get projector camera latency
    void projectStructuredLights();//will call gfx->drawRect, etc...
    
    void computeEM();
    void computeFM();
    
    //Attributes
    Camera_A* myCam;
    vector<float> camera2proj; //Camera to projector mapping
    vector<float> EM; //Texture storing the environmental light, row major
    vector<float> FM; //Texture storing the proj light, row major
    
    //Renderer_A* gfx;
};

#endif
