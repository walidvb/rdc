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
class Timer;

class RDC
{
public:
    bool simu;                                          //<! set to true when working without connected hardware(will use like taken pictures)
    
    RDC(){}
    RDC(int width, int height, Timer* timer);
    void init();
    void compensate(Image* srcImg, Image* dstImage);   //<! Called each frame, takes source image and returns compensated image
    void adapt(Mat* pix);                                 //<! adapts image prior to compensation(pix should be CV_64F)
    void computeLighting();                                 //<! computes env light and max light images
    void computeHomography(Sensor* cam, Renderer_A* gfx);   //<! projects patterns, and captures them
    void calibrateColors(Sensor* sensor, Renderer_A* gfx);  //<! calibrates all colors
    void grabEM(Sensor* cam, Renderer_A* gfx);
    void grabFM(Sensor* cam, Renderer_A* gfx);
    void grabAndSaveFrame(Sensor* cam);
    
    //logic
    bool getIsHomoComputed();
    bool getIsEMComputed();
    bool getIsFMComputed();
    bool getIsCalibrated();
    bool getIsEMRendered();
    bool getIsFMRendered();
    bool getIsRedRendered();
    bool getIsColorCalibrated();
    
    void setIsEMRendered(bool isIt);
    void setIsFMRendered(bool isIt);
        
    void setmagicE(double factor);
    void setmagicR(double factor);
    
    double magicE;
    double magicR;
    
private:
    //Private methods

    //Setup
    int getLatency();                                   //<! get projector camera latency
    Homo* homo;                                          //<! The object handling the homography
    //Preprocessing
    
    Mat EM;                                             //<! Matrix storing the environmental light, row major
    double EMmax;                                       //<! the maximum value found in EM
    Mat FM;                                             //<! Matrix storing the proj light, row major
    double FMmin;                                       //<! the minimum value found in FM
    int outWidth;                                       //<! the width of the output
    int outHeight;                                      //<! the height of the output
    Size outSize;
    
    //logic
    Timer* timer;
    bool isHomoComputed;
    bool isEMComputed;
    bool isFMComputed;
    bool isCalibrated;
    bool isEMRendered;
    bool isFMRendered;
    bool isColorCalibrated;
    double timeToWait;
};

#endif
