//
//  Controller.h
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#ifndef RDC_Controller_h
#define RDC_Controller_h

#include <opencv2/opencv.hpp>

class Sensor;
class Renderer_A;
class RDC;
class Image;
class Homo;
class Timer;
using namespace cv;

class Controller{
    
public:
    Controller();
    ~Controller();
    void init(int width, int height);
    void switchCam();
    void calibrate();                   //!< calibrates the camera/projector system
    void homography();                  //!< generates the homography matrix needed by the algorithm
    void process(Image& source, Image& dest);           //!< processes the frame that will be projected, and return it
    void process(Image& source);           //!< processes the frame that will be projected, and return it
    void sendCommand(char command);     //<! get a command from an upper layer
                                        //<! by pressing space, the app will stop waiting, and take a picture
    void mouseDown(int x, int y);
    void mouseUp(int x, int y);
    
    Renderer_A* getRenderer();
    bool isRDCCalibrated;
    RDC* getRDC();
    
    void setAdapt(bool dAdapt);
    void setSmooth(bool doSmooth);
    void setSmoothSize(int size);
    void setmagicR(float r);
    void setmagicE(float e);
    void reinit();
    int* getDeviceID();
    Sensor* getSensor();
private:
    bool simu;                                          //<! set to true when working without connected hardware(will use like taken pictures)

    //logic
    bool waitingKey = true;
    std::string sourceMedia;            //<! the media from which to load (is now a default)
    int deviceID;                       //<! the id of the capture device
    std::string resourcePath = "/Users/Gaston/dev/RDC/resources/";  //<! the path were resources are stored. should be relative to the app, but I don't know how to do that yet.
    bool gettingROI = false;
    int ROIStart[2];
    int ROIEnd[2];
    
    //objects
    Timer* timer;                       //<! the object handling all the timer stuff
    Sensor* media;                      //<! the loaded media / ftm only video is supported
    Sensor* captor;                     //<! the captor
    Renderer_A* gfx;               //<! well, the renderer
    RDC* rdc;                           //<! doing the magic. calibration, compensation matrix generation, and image processing
};

#endif
