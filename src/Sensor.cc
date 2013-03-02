//
//  Sensor.cc
//  RDC
//
//  Created by Gaston on 1/21/13.
//
//

#include "Sensor.h"
Sensor::Sensor() : width(800), height(600)
{
    frame = Image(width, height);
    cap = VideoCapture();
}

Sensor::Sensor(int width, int height) : width(width), height(height)
{
    frame = Image(width, height);
}

string Sensor::init(string source)
{
    cap = VideoCapture(source); // open the default camera
    if(!cap.isOpened())  // return -1 if we failed to open
    {
        cerr << "[Sensor] Failed to open " << source << endl;
        return "[Sensor] Failed to open";
    }
    else                //return the deviceID used
    {
        Mat tmp;
        cap >> tmp;
        width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        return source;
    }
}

int Sensor::init(int deviceID)
{
    if(cap.isOpened())
    {
        cout << "[Sensor] switching to " << deviceID << endl;
    }
    cap = VideoCapture(deviceID); // open the default camera
    if(!cap.isOpened())  // return -1 if we failed to open
    {
        cerr << "[Sensor] Failed to open capture device " << deviceID << ", the following devices are available: " << endl;
        return -1;
    }
    else                //return the deviceID used
    {
        Mat tmp;
        cap >> tmp;
        width = tmp.cols;
        height = tmp.rows;
        return deviceID;
    }
}

void Sensor::destroy()
{
    cap.release();
}
Image Sensor::grabFrame()
{
    Mat tmp;
    cap >> tmp;
    Image img(tmp);
    return img;
}

bool Sensor::isOpened()
{
    return cap.isOpened();
}

//Getters and Setters
int Sensor::getWidth() const
{
    return width;
}

int Sensor::getHeight() const
{
    return height;
}

//TOCHECK wanted to add a const here, but it won't let me..
Size Sensor::getSize() 
{
    if(!cap.isOpened())
    {
        return Size(-1, -1);
    }
    else
    {
        return Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    }    
}