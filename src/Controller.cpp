//
//  Controller.cpp
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#include "SimpleGUI.h"
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
    deviceID = 0;
}


Controller::~Controller()
{
    delete captor;
    delete gfx;
    delete rdc;
    delete timer;
}
Renderer_A* Controller::getRenderer()
{
    return this->gfx;
}
Sensor* Controller::getSensor()
{
    return this->captor;
}

void Controller::init(int width, int height)
{
    simu = false;
    cout << "[Controller] initializing system" << endl;
    timer = new www::Timer();
    rdc = new RDC(width, height, timer);
    rdc->setSimu(this->simu);
    rdc->init();
    if(!simu)
    {
        captor = new Sensor();
        captor->init(deviceID);
    }
    gfx = new Renderer_Cinder(width, height);
    isRDCCalibrated = false;
}

void Controller::reinit()
{
    rdc->reinit();
    timer->resetTimer();
    isRDCCalibrated = false;
}

void Controller::switchCam()
{
    captor->destroy();
    deviceID = (deviceID == 0) ? 1 : 0;
    captor->init(deviceID);
    cout << "[Controller]: changing Cam to " << deviceID << endl;
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
    }
}

void Controller::setmagicR(float r)
{
    rdc->magicR = (double)r;
}

void Controller::setmagicE(float e)
{
    rdc->magicE = (double)e;
}

void Controller::setAdapt(bool doAdapt)
{
    rdc->doAdapt = doAdapt;
}

void Controller::setSmooth(bool doSmooth)
{
    rdc->doSmooth = doSmooth;
}

void Controller::setSmoothSize(int size)
{
    rdc->smoothSize = max(0, 2*size-1);
}

int* Controller::getDeviceID()
{
    return &deviceID;
}

RDC* Controller::getRDC()
{
    return this->rdc;
}
void Controller::mouseDown(int x, int y)
{
        ROI[0] = x;
        ROI[1] = y;
}
void Controller::mouseUp(int x, int y)
{
        ROI[2] = x;
        ROI[3] = y;
        rdc->setROI(ROI[0], ROI[1], ROI[2], ROI[3]);
}