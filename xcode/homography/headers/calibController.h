
//
//  calibController.h
//  RDC
//
//  Created by Gaston on 1/17/13.
//
//

#ifndef RDC_calibController_h
#define RDC_calibController_h



#include "CameraCalibrator.h"


class CalibController{
    //init the system
public:
    //methods
    void init();                            //<! well, init..
    vector<string> takeAndSavePics();       //<! take multiple pictures and save them to disk
    void computeCalib();                    //<! compute the calibration matrix
    Mat getRealImage(Mat& original);        //<! returns the undistorted image
    void doCalib();                         //<! the whole package
                                            //<! takes pictures and does the calibration
    
    //Constructor
    CalibController(Size boardSize);
    
    //Getters and Setters
    Size getBoardSize();
private:
    CameraCalibrator* camCalib; //<! the object doing the calibration
    vector<string> fileList;    //<! the list of pictures taken
    Size boardSize;             //<! the size of the chessBoard
    Size frameSize;             //<! the resolution of the sensor/camera
    bool calibDone;             //<! used to know if calib has been done before or not.
};

#endif
