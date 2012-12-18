//
//  RDC.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//
#include "Camera_A.h"
#include "Renderer_A.h"
#include "RDC.h"
RDC::RDC(Camera_A* cam, Renderer_A* gfx) : cam(cam), gfx(gfx)
{
    camWidth = cam->getWidth();
    camHeight = cam->getWidth();
    gfxWidth = gfx->getWidth();
    gfxHeight = gfx->getHeight();
}

//Public methods
void RDC::calibrate()
{
    vector<float> img = cam->grabFrame();
    cout << "Camera pixels:" << endl;
    for (int i = 0; i < cam->getWidth(); i++)
    {
        for (int j = 0; j < cam->getHeight(); j++)
        {
            cout << img[ Tools::index(i, j, cam->getWidth()) ] << " ";
        }
        cout << endl;
    }
    projectStructuredLights();
}

vector<float> RDC::compensate(const vector<float>& srcImg)
{
    vector<float> dstImg;
    
    return dstImg;
}

//Private methods
void RDC::projectStructuredLights()
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

