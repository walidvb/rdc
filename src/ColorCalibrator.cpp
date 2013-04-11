//
//  ColorCalibrator.cpp
//  RDC
//
//  Created by Gaston on 3/18/13.
//
//
#include "ColorCalibrator.h"


//using namespace std;

ColorCalibrator::ColorCalibrator(Homo* homo, Timer* timer) :  homo(homo), timer(timer)
{
    timeToWait = 2;
    resources = "/Users/Gaston/dev/RDC/resources/";
    isCalibrated = false;
    colorDone = vector<bool>(BLUE-1, false);
    squareSize = sqrt((800*600)/SCALESCOUNT);
}

void ColorCalibrator::calibrate(Sensor* sensor, Renderer_A* gfx)
{
    if(!colorDone[RED])
    {
        calibrateColor(RED, sensor, gfx);
    }
    else if(!colorDone[GREEN])
    {
        calibrateColor(GREEN, sensor, gfx);

    }
    else if(!colorDone[BLUE])
    {
        calibrateColor(BLUE, sensor, gfx);
    }
}

void ColorCalibrator::calibrateColor(Colors color, Sensor* sensor, Renderer_A* gfx)
{
    string imgSrc;
    switch(color)
    {
        case RED:
            imgSrc = resources+"red.jpg";
            break;
        case GREEN:
            imgSrc = resources+"green.jpg";
            break;
        case BLUE:
            imgSrc = resources+"blue.jpg";
            break;
    }
    Image img(imgSrc);
    Image capture;
    gfx->drawImg(&img);
    if(timer->hasElapsed(timeToWait))
    {
        cout << "computing response function for " << color << endl;
        capture = sensor->grabFrame();
        computeResponse(color, &capture);
        timer->resetTimer();
    }

}

double ColorCalibrator::getCol(int index, Colors color, Image* img)
{
    int w = img->getWidth();

    int posX = index % (w/squareSize);
    int posY = (index - posX) / (w/squareSize);
    
    int x1 = posX*squareSize;
    int x2 = posX*(squareSize+1);
    int y1 = posY*squareSize;
    int y2 = posY*(squareSize+1);
    
    //1 is added/sub to prevent out of range errors
    Mat square = (*(img->getMat()))(Range(x1+1, x2-1), Range(y1+1, y2-1));
    Scalar myColor = mean(square);
    double value = myColor[color];
    return value;
}

void ColorCalibrator::computeResponse(Colors color, Image* capture)
{
    /*homo->warp(capture, Size(800, 600));
    //fill in the mapping
    for(int i = 0; i < SCALESCOUNT; i++)
    {
        colorMap[color][i] = getCol(i, color, capture);
    }
    */
    colorDone[color] = true;
    //if this is the last color tested
    if(color == colorDone.size()+1)
    {
        isCalibrated = true;
    }
}

//Getters&Setters
bool ColorCalibrator::getIsCalibrated()
{
    return isCalibrated;
}