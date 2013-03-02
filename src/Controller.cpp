//
//  Controller.cpp
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#include "common.h"
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
    int resolution;
    /*do
     {
     cout << "Choose your resolution: " << endl;
     cout << "  1: 480p" << endl;
     cout << "  2: 576p" << endl;
     cout << "  3: 720p" << endl;
     cin >> resolution;
     resolution--:
     }while (resolution != 0 || resolution != 1 || resolution != 2 );
     */
    
    cout << "[Controller] initializing system" << endl;
    captor = new Sensor();
    renderer = new Renderer_Cinder(width, height);
    rdc = new RDC(width, height);
    rdc->init(resolution);
    //media = new Sensor();
    //media->init(sourceMedia);
    isRDCCalibrated = false;
}

void Controller::calibrate()
{
    if(!captor->isOpened())
    {
        captor->init(deviceID);
    }
    //Compute homography, and get surface's properties
    if(!rdc->getIsCalibrated())
    {
        if(!rdc->getIsHomoComputed())
        {
            cout << "[Controller] calibrating system" << endl;
            
            rdc->computeHomography(captor, renderer);
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
            captor->destroy();
        }
    }
    else
    {
        cout << "[Controller] system calibrated" << endl;
    }
}

void Controller::process(Image& img)
{
    cout << "[Controller] processing image" << endl;
    rdc->compensate(&img, &img);
}

void Controller::sendCommand(char command)
{
    if(command=='e')
    {
        rdc->setIsEMRendered(true);
    }
    else if(command=='z')
    {
        rdc->setIsFMRendered(true);
    }
}