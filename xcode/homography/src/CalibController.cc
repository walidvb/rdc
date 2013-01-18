//
//  CalibController.cc
//  RDC
//
//  Created by Gaston on 1/17/13.
//
//

#include "CalibController.h"

CalibController::CalibController() : calibDone(false)
{
    boardSize = Size(6,4);
    
    //temporary use, see init()
    string filePath = "/Users/Gaston/Desktop/testChessboard.png";
    Mat image = imread(filePath, CV_LOAD_IMAGE_COLOR);
    frameSize = image.size();
    camCalib = new CameraCalibrator();
}
void CalibController::init()
{
    // TODO:
    // get frame size from the camera/Sensor?

}

vector<string> CalibController::takeAndSavePics()
{
    // TODO:
    // get a camera working in there, using a Sensor?
    
    string filePath = "/Users/Gaston/Desktop/testChessboard.png";
    fileList.push_back(filePath);
    return fileList;
}

void CalibController::computeCalib()
{
   
    camCalib->addChessboardPoints(fileList, boardSize);
    camCalib->calibrate(frameSize);
}

void CalibController::doCalib()
{
    takeAndSavePics();
    computeCalib();
    calibDone == true;
}

Mat CalibController::getRealImage(Mat& original)
{
    if(!calibDone)
    {
        doCalib();
    }
    return camCalib->remap(original);
}



//Getters and Setters
Size CalibController::getBoardSize()
{
    return boardSize;
}