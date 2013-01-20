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

void Sensor::stop()
{
    cap.release();
    bufferedImages.empty();
}

Mat Sensor::grabFrame()
{
    cap >> frame;
    return frame;
}

void saveFrame()
{
    imwrite(frame);
}