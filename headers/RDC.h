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

//enum res {r854x480, r1024x576, r1280x720};
enum res {pfalse, p480, p576, p720};
class RDC
{
public:
    RDC(){}
    RDC(int width, int height);
    void init(int resolution);
    void compensate(Image* srcImg, Image* dstImage);   //<! Called each frame, takes source image and returns compensated image
    void simulateWall(Image* srcImg, Image* dstImg, Image* wall);   //<! writes back to dstImg, as per the formula R = EM + I*FM. named ater its function, simulating the wall
    void computeLighting();                                 //<! computes env light and max light images
    void computeHomography(Sensor* cam, Renderer_A* gfx);   //<! projects patterns, and captures them
    void grabEM(Sensor* cam, Renderer_A* gfx);
    void grabFM(Sensor* cam, Renderer_A* gfx);
    
    void wait(int ms = 2000) const;//for debugging purpose
    
    //logic
    bool getIsHomoComputed();
    bool getIsEMComputed();
    bool getIsFMComputed();
    bool getIsCalibrated();
    bool getIsEMRendered();
    bool getIsFMRendered();

    void setIsEMRendered(bool isIt);
    void setIsFMRendered(bool isIt);
private:
    //Private methods

    //Setup
    int getLatency();                                   //<! get projector camera latency
    Homo* homo;                                          //<! The object handling the homography
    
    //Preprocessing
                                                         //<! used to fill max and min light images
    
    Mat camera2proj;                                    //<! Camera to projector mapping
    Mat EM;                                             //<! Matrix storing the environmental light, row major
    Mat FM;                                             //<! Matrix storing the proj light, row major

    int outWidth;                                           //<! the width of the output
    int outHeight;                                          //<! the height of the output
    int resolution;                                         //<! the resolution of the output, as defined per enum res up there, but not fucking taking it because it ain't no int
    
    //logic
    bool isHomoComputed;
    bool isEMComputed;
    bool isFMComputed;
    bool isCalibrated;
    bool isEMRendered;
    bool isFMRendered;
};

#endif
