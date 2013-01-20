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
    
    //for use with the image from the book, testChessboard
    //boardSize = Size(6,4);
    
    //init the system
    CalibController calibControl(boardSize);
    //Load the images
    string filePath = "/Users/Gaston/dev/RDC/tmp/IMG_0701.JPG";
    //filePath = "/Users/Gaston/dev/RDC/tmp/testChessboard.png";

    Mat image = imread(filePath, CV_LOAD_IMAGE_COLOR);
    Mat undisto = calibControl.getRealImage(image);
    
    
    
    // output vectors of image points
    std::vector<cv::Point2f> imageCorners;
    // Get the chessboard corners
    bool found = findChessboardCorners(image, boardSize, imageCorners);
    //Draw the corners
    drawChessboardCorners(image, boardSize, imageCorners, found); // corners have been found
    
    //Resize the images to a more reasonable size before treatment
    resize(image, image, Size(800, 800*image.size().height/image.size().width) );
    imshow( "Before remap", image );                   // Show our image inside it.
        
    //Resize the images to a more reasonable size before treatment
    resize(undisto, undisto, Size(800, 800*undisto.size().height/undisto.size().width) );
    //Draw the image
    imshow( "After remap", undisto );                   // Show our image inside it.
    
    cvWaitKey(0);
    cvDestroyWindow("Display window");
    cout << "application ended: merci au revoir" << endl;
    return 0;
    

}


#endif