//
//  CalibController.cc
//  RDC
//
//  Created by Gaston on 1/17/13.
//
//

#include "CalibController.h"

CalibController::CalibController(Size boardSize, Sensor* captor) : calibDone(false), boardSize(boardSize)
{
    //temporary use, see init()
    string filePath = "/Users/Gaston/dev/RDC/tmp/IMG_0693.JPG";
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
    for(int i = 693; i <= 704; i++)
    {
        string filePath = "/Users/Gaston/dev/RDC/tmp/IMG_0";
        //used to create the filepath
        stringstream ss;
        string index;
        ss << i;
        ss >> index;
        filePath += index;
        filePath += ".JPG";
        
        //filePath = "/Users/Gaston/Desktop/testChessboard.png";
        fileList.push_back(filePath);
    }
    return fileList;
}

void CalibController::computeCalib()
{
   
    camCalib->addChessboardPoints(fileList, boardSize);
    cout << "Calibration quality: " << camCalib->calibrate(frameSize);
}

void CalibController::doCalib()
{
    cout << "taking pictures..." << endl;
    takeAndSavePics();
    cout << " computing calibration coefficient..." << endl;
    computeCalib();
    cout << "Done!" << endl;
    calibDone = true;
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