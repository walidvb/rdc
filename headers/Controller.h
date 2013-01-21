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

class Controller{
    
public:
    Controller();
    ~Controller();
    void init(int width, int height);
    void calibrate();   //!< generates the homography matrix needed by the algorithm
    void process();     //!< processes the frame that will be projected, and return it
    void draw();        //<! draw the image, might not be the right place?
    
private:
    Sensor* media;
    Sensor* captor;
    Renderer_A* renderer;
    RDC* rdc;
    std::string sourceMedia;
    int deviceID;
};

#endif
