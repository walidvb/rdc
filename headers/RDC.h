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
class Homo;

class RDC
{
public:
    RDC(){}
    RDC(int width, int height);
    void init();
    void calibrate(Sensor* cam, Renderer_A* gfx);      //<! Called once, starts the calibration and computes needed values for compensation
    void computeLighting();                            //<! Fill env light and max light images
    void compensate(Image& srcImg, Image& dstImage);   //<! Called each frame, takes source image and returns compensated image
    
    //Getters
    Image* getEM();                                //<! returns EM, only used for testing purposes
    
private:
    //Private methods
    //Setup
    int getLatency();                                   //<! get projector camera latency
    void projectPatterns(Renderer_A* gfx);      //<! project patterns, take a picture and
    void computeHomography(Sensor* cam);
    Homo* homo;                                          //<! The object handling the homography
    
    //Preprocessing
    void getSurface(Image* source, Image* target); //<! fill target with pixels from source, homographied
                                                         //<! used to fill max and min light images
    
    Mat camera2proj;                                    //<! Camera to projector mapping
    Image EM;                                             //<! Matrix storing the environmental light, row major
    Image FM;                                             //<! Matrix storing the proj light, row major

    int outWidth;                                           //<! the width of the output
    int outHeight;                                          //<! the height of the output
};

#endif
