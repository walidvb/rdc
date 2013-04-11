//
//  Controller.cpp
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#include "common.h"
#include "Timer.h"
#include "Controller.h"
#include "Sensor.h"
#include "Renderer_Cinder.h"
#include "Renderer_CV.h"
#include "RDC.h"

using namespace cv;

Controller::Controller()
{
    deviceID = 1;
}


Controller::~Controller()
{
    delete captor;
    delete gfx;
    delete rdc;
    delete media;
}
Renderer_A* Controller::getRenderer()
{
    return this->gfx;
}


void Controller::init(int width, int height)
{
    simu = false;
    cout << "[Controller] initializing system" << endl;
    timer = new Timer();
    rdc = new RDC(width, height, timer);
    rdc->simu = this->simu;
    rdc->init();
    if(!simu)
    {
        captor = new Sensor();
        captor->init(deviceID);
    }
    gfx = new Renderer_Cinder(width, height);

    
    //media = new Sensor();
    //media->init(sourceMedia);
    isRDCCalibrated = false;
}

void Controller::calibrate()
{
    //Compute homography, and get surface's properties
    if(!rdc->getIsCalibrated())
    {
        if(simu)
        {
            isRDCCalibrated = true;
            return;
        }
        else if(!rdc->getIsHomoComputed())
        {
            rdc->computeHomography(captor, gfx);
            return;
        }
        else if(!rdc->getIsColorCalibrated())
        {
            rdc->calibrateColors(captor, gfx);
            return;
        }
        else if(!rdc->getIsEMComputed())//if EM pas ok
        {
            rdc->grabEM(captor, gfx);
            return;
        }
        else if(!rdc->getIsFMComputed())//if FM pas ok
        {
            rdc->grabFM(captor, gfx);
            return;
        }
        else if(!rdc->getIsLightComputed())
        {
            rdc->computeLighting();
            return;
        }
        else if(!rdc->getIsFMMinEMMaxDone())
        {
            rdc->getFMMinEMMax();
        }
        else
        {
            isRDCCalibrated = true;
        }
    }
    else
    {
        cout << "[Controller] system calibrated" << endl;
    }
}

void Controller::process(Image& source, Image& dest)
{
    //cout << "[Controller] processing image" << endl;
    rdc->compensate(&source, &dest);
}

void Controller::process(Image& source)
{
    this->process(source, source);
}

void Controller::sendCommand(char command)
{
    switch(command)
    {
        case 'g':
            rdc->grabAndSaveFrame(captor);
            break;
        case 'n':
            rdc->setmagicE(0.1);
            break;
        case 'm':
            rdc->setmagicE(-0.1);
            break;
        case 'j':
            rdc->setmagicR(0.1);
            break;
        case 'k':
            rdc->setmagicR(-0.1);
            break;
    }
}

void Controller::mouseDown(int x, int y)
{
    gettingROI = true;
    ROIStart[0] = x;
    ROIStart[1] = y;
}
void Controller::mouseUp(int x, int y)
{
    gettingROI = false;
    ROIEnd[0] = x;
    ROIEnd[1] = y;
    rdc->setROI(ROIStart[0], ROIStart[1], ROIEnd[0], ROIEnd[1]);
    
}