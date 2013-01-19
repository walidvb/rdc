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

using namespace cv;
using namespace std;


int main (int argc, const char * argv[])
{
    
    
    
    // number of corners on the chessboard
    Size boardSize(5,4);
    boardSize = Size(6,5);
    //init the system
    CalibController calibControl(boardSize);
    //Load the images
    string filePath = "/Users/Gaston/Desktop/testChessboard.png";//dev/RDC/tmp/IMG_0704.JPG";
    Mat image = imread(filePath, CV_LOAD_IMAGE_COLOR);
    
    //Resize the images to a more reasonable size before treatment
    resize(image, image, Size(800, 800*image.size().height/image.size().width) );
    
    // output vectors of image points
    std::vector<cv::Point2f> imageCorners;
    // Get the chessboard corners
    bool found = findChessboardCorners(image, boardSize, imageCorners);
    //Draw the corners
    drawChessboardCorners(image, boardSize, imageCorners, found); // corners have been found
    
    imshow( "Before remap", image );                   // Show our image inside it.
        
    //image = calibControl.getRealImage(image);
    //Draw the image
    imshow( "After remap", calibControl.getRealImage(image) );                   // Show our image inside it.
    
    cvWaitKey(0);
    cvDestroyWindow("Display window");
    
    return 0;
    

}


#endif