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
#include <unistd.h>
using namespace cv;
using namespace std;


int main (int argc, const char * argv[])
{
    //init the system
    CameraCalibrator camCalib;
    
    IplImage *img = cvCreateImage(cvSize(200, 100), IPL_DEPTH_8U, 3);
    
    //Load the images
    string filePath = "/Users/Gaston/Desktop/testChessboard.png";
    cout << "trying to read from " << filePath << endl;
    Mat image = imread(filePath, CV_LOAD_IMAGE_COLOR);
    
    //Find the corners
    
    // output vectors of image points
    std::vector<cv::Point2f> imageCorners;
    // number of corners on the chessboard
    Size boardSize(6,4);
    // Get the chessboard corners
    bool found = findChessboardCorners(image,boardSize, imageCorners);
    //Draw the corners
    drawChessboardCorners(image, boardSize, imageCorners, found); // corners have been found
     
    //camCalib.addChessboardPoints(vector<string> fileList {filePath}, boardSize);
    
    
    //Draw the image
    cvNamedWindow("img", CV_WINDOW_AUTOSIZE);
    //cvShowImage("img", img);
    imshow( "Display window", image );                   // Show our image inside it.
    cvWaitKey(0);
    cvDestroyWindow("img");
    cvReleaseImage(&img);
    
    return 0;
    //Create an instance
    

}


#endif