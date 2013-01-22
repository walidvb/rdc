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
    deviceID = 0;
    sourceMedia = resourcePath + "media.mov";
}


Controller::~Controller()
{
    delete captor;
    delete renderer;
    delete rdc;
    delete media;
}

void Controller::init(int width, int height)
{
    captor = new Sensor();
    renderer = new Renderer_Cinder(width, height);
    rdc = new RDC();
    //media = new Sensor();
    //captor->init(deviceID);
    //media->init(sourceMedia);
    testFrame = new Image(resourcePath+"lena.bmp");
}

void Controller::calibrate()
{
    //TODO
    //Get the homography matrice
    rdc->calibrate(captor, renderer);
}

void Controller::process()
{
    //TOCHECK: ftm only display test image
    Image frame = Image(*testFrame);
    renderer->drawImg(*testFrame, FULL);
    //Grab frame from media
    //Image frame = media->grabFrame();
    //renderer->drawImg(frame, FULL);
    //process it
    frame = rdc->compensate(frame);
    //render it
    renderer->drawImg(frame, FULL);
}

void Controller::draw()
{
    
}