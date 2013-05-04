//
//  CameraCalibrator.h
//  RDC
//
//  Created by Gaston on 1/17/13.
//
//

#ifndef __RDC__CameraCalibrator__
#define __RDC__CameraCalibrator__

#include "common.h"

class CameraCalibrator
{
    // input points:
    std::vector<vector<cv::Point3f> > objectPoints; //<! the points in world coordinates
    std::vector<vector<cv::Point2f> > imagePoints;  //<! the point positions in pixels
    
    cv::Mat cameraMatrix; //<! output Matrices
    cv::Mat distCoeffs; //<! output Matrices
    
    int flag; //<! flag to specify how calibration is done
    
    cv::Mat map1,map2; //<! used in image undistortion
    bool mustInitUndistort;
    
public:
    CameraCalibrator();
    int addChessboardPoints(const vector<string>& filelist, cv::Size & boardSize);      //<! Open chessboard images and extract corner points
    void addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners);     //<! Add scene points and corresponding image points
    double calibrate(cv::Size &imageSize); //<! Calibrate the camera, returns the re-projection error
    cv::Mat remap(const cv::Mat &image); //<! remove distortion in an image (after calibration)

};

#endif /* defined(__RDC__CameraCalibrator__) */
