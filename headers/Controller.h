//
//  Controller.h
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#ifndef RDC_Controller_h
#define RDC_Controller_h

namespace www{ class Timer;}
namespace mowa{namespace sgui {class SimpleGUI;}}
class Sensor;
class Renderer_A;
class RDC;
class Image;
class Homo;

class Controller{
    
public:
    Controller();
    ~Controller();
    // logic
    void init(int width, int height);
    void reinit();                      //<! restart the scan
    void switchCam();                   //!< switches camera source. only sources supported are 0 and 1
    void calibrate();                   //!< calibrates the camera/projector system
    void process(Image& source, Image& dest);   //!< processes the frame that will be projected and saves to dest
    void process(Image& source);        //!< processes the frame that will be projected, and return it
    
    //UI
    void sendCommand(char command);     //<! send a command
    void mouseDown(int x, int y);       //<! used to set a region
    void mouseUp(int x, int y);         //<! used to complete region, and send the ROI to RDC
    
    //Getters & Setters
    //parameters, mostly passed down to the controller
    Renderer_A* getRenderer();
    bool isRDCCalibrated;
    RDC* getRDC();
    Sensor* getSensor();
    int* getDeviceID();
    
    void setAdapt(bool dAdapt);
    void setSmooth(bool doSmooth);
    void setSmoothSize(int size);
    void setmagicR(float r);
    void setmagicE(float e);
    
private:
    //logic
    bool simu;                          //<! set to true when working without connected hardware
    int deviceID;                       //<! the id of the capture device
    std::string resourcePath = "/Users/Gaston/dev/RDC/resources/";  //<! the path were resources are stored. should be relative to the app, but I don't know how to do that yet.
    int ROI[4];                         //<! stores 4 corners for FMMin
    
    //objects
    www::Timer* timer;                       //<! the object handling all the timer stuff
    Sensor* captor;                     //<! the captor
    Renderer_A* gfx;                    //<! well, the renderer
    RDC* rdc;                           //<! doing the magic. calibration, compensation matrix generation, and image processing
};

#endif
