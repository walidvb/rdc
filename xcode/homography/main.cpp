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
        
    //Load the images
    string filePath = "/Users/Gaston/Desktop/testChessboard.png";
    cout << "trying to read from " << filePath << endl;
    Mat image = imread(filePath, CV_LOAD_IMAGE_COLOR);
    
    //Find the corners
    Size boardSize(6,4);
    /*
    // output vectors of image points
    std::vector<cv::Point2f> imageCorners;
    // number of corners on the chessboard
    // Get the chessboard corners
    bool found = findChessboardCorners(image,boardSize, imageCorners);
    //Draw the corners
    drawChessboardCorners(image, boardSize, imageCorners, found); // corners have been found
    */
    vector<string> fileList;
    fileList.push_back(filePath);
    camCalib.addChessboardPoints(fileList, boardSize);
    Size s(image.rows, image.cols);
    camCalib.calibrate(s);
    image = camCalib.remap(image);
    
    //Draw the image

    imshow( "Display window", image );                   // Show our image inside it.
    cvWaitKey(0);
    cvDestroyWindow("Display window");
    
    return 0;
    

}


#endif