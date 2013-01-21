//
//  main.cpp
//  homography
//
//  Created by Gaston on 1/17/13.
//
//

#ifndef HOMO
#define HOMO

#include <iostream>
#include <opencv2/opencv.hpp>
#include "CameraCalibrator.h"
#include "CalibController.h"
#include "Sensor.h"

using namespace cv;
using namespace std;


int main (int argc, const char * argv[])
{
    
    Sensor capture;
    capture.init("/Users/Gaston/dev/RDC/resources/media.mov");
    
    // number of corners on the chessboard
    Size boardSize(5,4);
    
    //init the system
    Mat image;
    while(1)
    {
        
              //Resize the images to a more reasonable size before treatment
        //resize(image, image, Size(800, 800*image.size().height/image.size().width) );
        
        imshow( "Camera: ", capture.grabFrame() );                   // Show our image inside it.
        if(waitKey(30) >=0 )
        {
            break;
        }

    }

    cvDestroyWindow("Display window");
    cout << "application ended: merci au revoir" << endl;
    return 0;
    
    
}


#endif