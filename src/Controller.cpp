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

Controller::Controller()
{
    deviceID = 1;
}


Controller::~Controller()
{
    delete captor;
    delete renderer;
    delete rdc;
    delete media;
}
Renderer_A* Controller::getRenderer()
{
    return this->renderer;
}


void Controller::init(int width, int height)
{    
    cout << "[Controller] initializing system" << endl;
    timer = new Timer();
    captor = new Sensor();
    renderer = new Renderer_Cinder(width, height);
    rdc = new RDC(width, height, timer);
    rdc->init();
    captor->init(deviceID);
    //media = new Sensor();
    //media->init(sourceMedia);
    isRDCCalibrated = false;
}

void Controller::calibrate()
{

    if(!captor->isOpened())
    {
        //captor->init(deviceID);
    }
    //Compute homography, and get surface's properties
    if(!rdc->getIsCalibrated())
    {
        if(!rdc->getIsHomoComputed())
        {
            cout << "[Controller] calibrating system" << endl;
            rdc->computeHomography(captor, renderer);
        }
        else if(!rdc->getIsColorCalibrated())
        {
            cout << "[Controller] calibrating colors..." << endl;
            rdc->calibrateColors(captor, renderer);
        }
        else if(!rdc->getIsEMComputed())//if EM pas ok
        {
            rdc->grabEM(captor, renderer);
        }
        else if(!rdc->getIsFMComputed())//if FM pas ok
        {
            rdc->grabFM(captor, renderer);
        }
        else
        {
            rdc->computeLighting();
            isRDCCalibrated = true;
            //captor->destroy();
        }
    }
    else
    {
        cout << "[Controller] system calibrated" << endl;
    }
}

void Controller::process(Image& source, Image& dest)
{
    cout << "[Controller] processing image" << endl;
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
        case 'e':
            rdc->setIsEMRendered(true);
            break;
        case 'z':
            rdc->setIsFMRendered(true);
            break;
        case 'p':
            
            break;
        case 'g':
            rdc->grabAndSaveFrame(captor);
            break;
        case 'n':
            rdc->setmagicE(0.1);
            break;
        case 'm':
            rdc->setmagicE(-0.1);
            break;
    }
}