//
//  CameraCalibrator.cc
//  RDC
//
//  Created by Gaston on 1/17/13.
//
//

#include "CameraCalibrator.h"

CameraCalibrator::CameraCalibrator() : flag(0), mustInitUndistort(true) {};

int CameraCalibrator::addChessboardPoints(
                                          const vector<string>& filelist,
                                          Size & boardSize) {
    // the points on the chessboard
    std::vector<cv::Point2f> imageCorners;
    std::vector<cv::Point3f> objectCorners;
    // 3D Scene Points:
    // Initialize the chessboard corners
    // in the chessboard reference frame
    // The corners are at 3D location (X,Y,Z)= (i,j,0)
    for (int i=0; i<boardSize.height; i++) {
        for (int j=0; j<boardSize.width; j++) {
            objectCorners.push_back(cv::Point3f(i, j, 0.0f));
        }
    }
    // 2D Image points:
    Mat image; // to contain chessboard image
    int successes = 0;
    // for all viewpoints
    for (int i=0; i<filelist.size(); i++) {
        // Open the image
        image = imread(filelist[i],0);
        cout << filelist[i] << ": ";
        // Get the chessboard corners
        bool found = findChessboardCorners(image, boardSize, imageCorners);
        if(!found)
        {
            cout << "[CamCalib] no ";
        }
        cout << "corners found" << endl;
        
        if(found)
        {
            // Get subpixel accuracy on the corners
            cornerSubPix(image, imageCorners,
                         Size(5,5),
                         Size(-1,-1),
                         TermCriteria(TermCriteria::MAX_ITER +
                                      TermCriteria::EPS,
                                      30,      // max number of iterations
                                      0.1));  // min accuracy
            //If we have a good board, add it to our data
            if (imageCorners.size() == boardSize.area()) {
                // Add image and scene points from one view
                addPoints(imageCorners, objectCorners);
                
                successes++;
            }
        }
    }
    return successes;
}

// Add scene points and corresponding image points
void CameraCalibrator::addPoints(const std::vector<cv::Point2f>&
                                 imageCorners, const std::vector<cv::Point3f>& objectCorners) {
    // 2D image points from one view
    imagePoints.push_back(imageCorners);
    // corresponding 3D scene points
    objectPoints.push_back(objectCorners);
}


double CameraCalibrator::calibrate(cv::Size &imageSize) //<! Calibrate the camera returns the re-projection error
{
    // undistorter must be reinitialized
    mustInitUndistort= true;
    //Output rotations and translations
    std::vector<cv::Mat> rvecs, tvecs;
    // start calibration
    return
    calibrateCamera(objectPoints, // the 3D points
                    imagePoints,  // the image points
                    imageSize,    // image size
                    cameraMatrix, // output camera matrix
                    distCoeffs,   // output distortion matrix
                    rvecs, tvecs, // Rs, Ts
                    flag);        // set options
}

// remove distortion in an image (after calibration)
cv::Mat CameraCalibrator::remap(const cv::Mat &image) {
    cv::Mat undistorted;
    if (mustInitUndistort) { // called once per calibration
        cv::initUndistortRectifyMap(
                                    cameraMatrix,  // computed camera matrix
                                    distCoeffs,
                                    cv::Mat(),
                                    cv::Mat(),
                                    // computed distortion matrix
                                    // optional rectification (none)
                                    // camera matrix to generate undistorted
                                    image.size(),  // size of undistorted
                                    CV_32FC1,      // type of output map
                                    map1, map2);   // the x and y mapping functions
        mustInitUndistort= false;
    }
    // Apply mapping functions
    cv::remap(image, undistorted, map1, map2,
              cv::INTER_LINEAR); // interpolation type
    return undistorted;
}