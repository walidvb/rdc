
//
//  calibController.h
//  RDC
//
//  Created by Gaston on 1/17/13.
//
//

#ifndef RDC_calibController_h
#define RDC_calibController_h

//#include <iostream>
//#include <opencv2/opencv.hpp>

#include "CameraCalibrator.h"

using namespace std;
using namespace cv;

class CalibController{
    //init the system
public:
    //methods
    void init();    //<! well, init..
    vector<string> takeAndSavePics();       //<! take multiple pictures and save them to disk
    void computeCalib(); //<! compute the calibration matrix
    Mat getRealImage(Mat& original); //<! returns the undistorted image
    void doCalib(); //<! the whole package
                    //<! takes pictures and does the calibration
    
    //Constructor
    CalibController();
    
    //Getters and Setters
    Size getBoardSize();
private:
    CameraCalibrator* camCalib; //<! the object doing the calibration
    vector<string> fileList;    //<! the list of pictures taken
    Size boardSize;             //<! the size of the chessBoard
    Size frameSize;             //<! the resolution of the sensor/camera
    /*
     //Load the images
     string filePath = "/Users/Gaston/Desktop/testChessboard.png";
     cout << "trying to read from " << filePath << endl;
     Mat image = imread(filePath, CV_LOAD_IMAGE_COLOR);
     
     //Find the corners
     Size boardSize(6,4);
     vector<string> fileList;
     fileList.push_back(filePath);
     camCalib.addChessboardPoints(fileList, boardSize);
     Size s(image.rows, image.cols);
     camCalib.calibrate(s);
     image = camCalib.remap(image);
     
     
     std::vector<cv::Point2f> imageCorners;
     bool found = findChessboardCorners(image,boardSize, imageCorners);
     drawChessboardCorners(image, boardSize, imageCorners, found); // corners have been found
     */
    
};

#endif
