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
    renderer = new Renderer_CV(width, height);
    rdc = new RDC();
    rdc->init();
    //media = new Sensor();
    //captor->init(deviceID);
    //media->init(sourceMedia);
    testFrame = new Image(resourcePath+"chesspic.jpg");
}

void Controller::calibrate()
{
    //TODO
    //Get the homography matrice
    rdc->calibrate(captor, renderer);
}

void Controller::process(Image& img)
{
    //renderer->drawImg(img, FULL);//For test purpose
    rdc->compensate(img, img);
    renderer->drawImg(img, FULL);
}

void Controller::draw()
{
    
}