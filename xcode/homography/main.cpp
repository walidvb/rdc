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
#import <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main (int argc, const char * argv[])
{
    IplImage *img = cvCreateImage(cvSize(200, 100), IPL_DEPTH_8U, 3);
    
    cvLine(img, cvPoint(10, 10), cvPoint(150, 80), cvScalar(0,255,0,0), 1, 8, 0);
    
    cvNamedWindow("img", CV_WINDOW_AUTOSIZE);
    cvShowImage("img", img);
    
    cvWaitKey(0);
    cvDestroyWindow("img");
    cvReleaseImage(&img);
    return 0;
    //Create an instance 
}

void init()
{
    
}
#endif