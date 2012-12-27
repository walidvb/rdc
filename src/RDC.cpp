//
//  RDC.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//
#include "Sensor_A.h"
#include "Renderer_A.h"
#include "RDC.h"

//Public methods
void RDC::calibrate(Sensor_A* cam, Renderer_A* gfx)
{
    Image img = cam->grabFrame();
    cout << "Camera pixels:" << endl;
    for (int i = 0; i < cam->getWidth(); i++)
    {
        for (int j = 0; j < cam->getHeight(); j++)
        {
            cout << img.pixelAt(i, j) << " ";
        }
        cout << endl;
    }
    projectStructuredLights(gfx);
    
    //TODO compute compensation matrix
}

Image RDC::compensate(const Image& srcImg)
{
    Image dstImg(srcImg.width, srcImg.height);
    for (int i = 0; i < srcImg.width; i++)
    {
        for (int j = 0 ; j < srcImg.height; j++)
        {
            dstImg.pixelWrite(srcImg.pixelAt(i,j)+1, i, j);
        }
    }
    return dstImg;
    //TODO compensate #1 test with dummy matrix
}

//Private methods
void RDC::projectStructuredLights(Renderer_A* gfx)
{
    cout << "projecting structured lights" << endl;
    float xOffset = 20.0;
    float width_ = 20.0;
    gfx->drawStripeVert(xOffset, width_);
}

void RDC::computeEM()
{
}

void RDC::computeFM()
{
}

