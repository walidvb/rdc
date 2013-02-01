//
//  Controller.h
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#ifndef RDC_Controller_h
#define RDC_Controller_h

class Sensor;
class Renderer_A;
class RDC;
class Image;
class Homo;

class Controller{
    
public:
    Controller();
    ~Controller();
    void init(int width, int height);
    void calibrate();           //!< calibrates the camera/projector system
    void homography();          //!< generates the homography matrix needed by the algorithm
    void process(Image& img);             //!< processes the frame that will be projected, and return it
    void draw();                //<! draw the image, might not be the right place?
    
private:
    Sensor* media;              //<! the loaded media / ftm only video is supported
    Sensor* captor;             //<! the captor
    Renderer_A* renderer;       //<! well, the renderer
    RDC* rdc;                   //<! he does the magic. calibration, compensation matrix generation, and image processing
    
    Image* testFrame;            //<! just a test frame, to avoid loading a video. Should be removed for final product
    
    std::string sourceMedia;    //<! the media from which to load (is now a default)
    int deviceID;               //<! the id of the capture device
    std::string resourcePath = "/Users/Gaston/dev/RDC/resources/";  //<! the path were resources are stored. should be relative to the app, but I don't know how to do that yet.
};

#endif
