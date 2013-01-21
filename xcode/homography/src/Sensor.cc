//
//  Sensor.cc
//  RDC
//
//  Created by Gaston on 1/20/13.
//
//

#include "Sensor.h"

Sensor::Sensor()
{
    
}

int Sensor::init(int videoID)
{
    if(cap.isOpened())
    {
        cout << "switching to " << videoID << endl;
    }
    
    cap = VideoCapture(videoID); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
    {
        return -1;
    }
    else
    {
        Mat tmp;
        cap >> tmp;
        width = tmp.cols;
        height = tmp.rows;
        return videoID;
    }
}

string Sensor::init(string filepath)
{
    if(cap.isOpened())
    {
        cout << "opening " << filepath << endl;
    }
    
    cap = VideoCapture(filepath); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
    {
        return "failed to open " + filepath;
    }
    else
    {
        Mat tmp;
        cap >> tmp;
        width = tmp.cols;
        height = tmp.rows;
        return filepath;
    }
}


Mat Sensor::grabFrame()
{
    cap >> frame;
    return frame;
}
