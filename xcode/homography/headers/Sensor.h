//
//  Sensor.h
//  RDC
//
//  Created by Gaston on 1/20/13.
//
//

#ifndef RDC_Sensor_h
#define RDC_Sensor_h

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Sensor
{
public:
    //Methods
    Sensor();
    Sensor(int width, int height);
    int init(int videoID = 0);   //<! inits a video device, and returns its ID
    bool init(string filepath);
    void stop();                 //<! stops the capture device communication
    Mat grabFrame();             //<! updates local frame, and returns it as well
    void saveFrame();            //<! writes current frame to disk
    void saveFrame(string path); //<! writes current frame to disk
    
    //Getters and Setters
    int getWidth() const;
    int getHeight() const;
    
private:
    //Attributes
    vector<Mat*> bufferedImages; //<! used to store tmp images that will be used for calibration
    VideoCapture cap;            //<! the openCV capture object
    Mat frame;                   //<! the current image. TODO: switch to Image? or change Image to Mat?
    int width;
    int height;
};

#endif
