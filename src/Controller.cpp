//
//  Controller.cpp
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#include "Controller.h"
#include "SensorSim.h"
#include "Renderer_Cinder.h"
#include "SensorMediaSim.h"
#include "RDC.h"


Controller::~Controller()
{
    delete sensor;
    delete renderer;
    delete rdc;
    delete sensorMedia;
}

void Controller::init(int width, int height)
{
    sensor = new SensorSim();
    renderer = new Renderer_Cinder(width, height);
    rdc = new RDC();
    sensorMedia = NULL;
}

void Controller::calibrate()
{
    //TODO
    //Get the homography matrice
    rdc->calibrate(sensor, renderer);
}

void Controller::process()
{
    if(!sensorMedia)
    {
        sensorMedia = new SensorMediaSim(10,10);
    }
    
    Image frame = sensorMedia->grabFrame();
    renderer->drawImg(frame, FULL);
    frame = rdc->compensate(frame);
    renderer->drawImg(frame, FULL);
}

void Controller::draw()
{
    
}