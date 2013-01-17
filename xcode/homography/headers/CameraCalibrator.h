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
    // the points in world coordinates
    vector<vector<Point3f> > objectPoints;
    // the point positions in pixels
    vector<vector<Point2f> > imagePoints;
    // output Matrices
    Mat cameraMatrix;
    Mat distCoeffs;
    // flag to specify how calibration is done
    int flag;
    // used in image undistortion
    Mat map1,map2;
    bool mustInitUndistort;
public:
    CameraCalibrator();
    void test(){cout << "hello calib";};
    int addChessboardPoints(const vector<string>& filelist, Size & boardSize);      //<! Open chessboard images and extract corner points
    void addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners);     //<! Add scene points and corresponding image points
    double calibrate(cv::Size &imageSize); //<! Calibrate the camera, returns the re-projection error
    Mat remap(const cv::Mat &image); //<! remove distortion in an image (after calibration)

    #endif /* defined(__RDC__CameraCalibrator__) */
};