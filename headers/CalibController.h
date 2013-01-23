
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
#include "Sensor.h"

class CalibController{
public:
    //methods
    void init();                            //<! well, init..
    vector<string> takeAndSavePics();       //<! take multiple pictures and save them to disk
    void computeCalib();                    //<! compute the calibration matrix
    Mat getRealImage(Mat& original);        //<! returns the undistorted image
    void doCalib();                         //<! the whole package
                                            //<! takes pictures and does the calibration
    
    //Constructor
    CalibController(Size boardSize, Sensor* captor);
    
    //Getters and Setters
    Size getBoardSize();        //<! used i can't remember where...
private:
    CameraCalibrator* camCalib; //<! the object doing the calibration
    Sensor* capture;            //<! the device used to capture the scene, therefor allowing calibration
    vector<string> fileList;    //<! the list of pictures taken
    Size boardSize;             //<! the size of the chessBoard
    Size frameSize;             //<! the resolution of the sensor/camera
    bool calibDone;             //<! used to know if calib has been done before or not.
};

#endif
