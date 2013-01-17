//
//  homography.h
//  RDC
//
//  Created by Gaston on 1/16/13.
//
//

#ifndef RDC_homography_h
#define RDC_homography_h
#include <opencv2/opencv2>

using namespace cv;

class Homography
{
    IplImage *img = cvCreateImage(cvSize(200, 100), IPL_DEPTH_8U, 3);
    
    cvLine(img, cvPoint(10, 10), cvPoint(150, 80), cvScalar(0,255,0,0), 1, 8, 0);
    
    cvNamedWindow("img", CV_WINDOW_AUTOSIZE);
    cvShowImage("img", img);
    
}

#endif
