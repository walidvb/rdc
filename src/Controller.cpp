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
    int resolution;
    do
    {
        cout << "Choose your resolution: " << endl;
        cout << "  1: 480p" << endl;
        cout << "  2: 576p" << endl;
        cout << "  3: 720p" << endl;
        cin >> resolution;
    }while (resolution < 0 || resolution > 3);

    
    captor = new Sensor();
    renderer = new Renderer_CV(width, height);
    rdc = new RDC(width, height);
    rdc->init(resolution);
    //media = new Sensor();
    //captor->init(deviceID);
    //media->init(sourceMedia);
    testFrame = new Image(resourcePath+"chesspic.jpg");
}

void Controller::calibrate()
{
    //TODO
    //Get the homography matrice
    rdc->calibrateSystem(captor, renderer);
    //renderer->drawImg(rdc->getEM());
}

void Controller::process(Image& img)
{
    //renderer->drawImg(img, FULL);//For test purpose
    rdc->compensate(&img, &img);

    renderer->drawImg(&img, FULL);
}