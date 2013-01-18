//
//  CameraCalibrator.h
//  RDC
//
//  Created by Gaston on 1/17/13.
//
//

#ifndef __RDC__CameraCalibrator__
#define __RDC__CameraCalibrator__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class CameraCalibrator {
    // input points:
    vector<vector<Point3f> > objectPoints; //<! the points in world coordinates

    vector<vector<Point2f> > imagePoints;  //<! the point positions in pixels
    
    Mat cameraMatrix; //<! output Matrices
    Mat distCoeffs; //<! output Matrices
    
    int flag; //<! flag to specify how calibration is done
    
    Mat map1,map2; //<! used in image undistortion
    bool mustInitUndistort;
public:
    CameraCalibrator();
    int addChessboardPoints(const vector<string>& filelist, Size & boardSize);      //<! Open chessboard images and extract corner points
    void addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners);     //<! Add scene points and corresponding image points
    double calibrate(cv::Size &imageSize); //<! Calibrate the camera, returns the re-projection error
    Mat remap(const cv::Mat &image); //<! remove distortion in an image (after calibration)

    #endif /* defined(__RDC__CameraCalibrator__) */
};