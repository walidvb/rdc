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
class Renderer_A;
class RDC
{
public:
    RDC(Camera_A* cam, Renderer_A* gfx);
    void calibrate();   //Called once, starts the calibration and computes needed values for compensation
    vector<float> compensate(const vector<float>& srcImg); //Called each frame, takes source image and returns compensated image
    
private:
    //Private methods
    int getLatency(); //get projector camera latency
    void projectStructuredLights();//will call gfx->drawRect, etc...
    
    void computeEM(); //compute the environment light
    void computeFM(); // compute the max projected light
    
    //Attributes
    Camera_A* cam; //!< the camera used to capture the scene
    int camWidth;
    int camHeight;
    
    Renderer_A* gfx; //!< the engine used to render the pattern, and probably the image after that.
    int gfxWidth;
    int gfxHeight;
    vector<float> camera2proj; //Camera to projector mapping
    vector<float> EM; //Texture storing the environmental light, row major
    vector<float> FM; //Texture storing the proj light, row major
};

#endif
