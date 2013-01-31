//
//  RDC.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//
#include "Sensor.h"
#include "Renderer_A.h"
#include "RDC.h"

//Public methods
void RDC::calibrate(Sensor* cam, Renderer_A* gfx)
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

void RDC::computeHomography()
{
    
}

Image RDC::compensate(Image& srcImg, Image& dstImg)
{
    int w = srcImg.width;
    int h = srcImg.height;
    //make sure dst is the correct size
    dstImg.pixels.create(h, w, srcImg.pixels.type());

    // number of lines
    int nl= h;
    // total number of elements per line
    int nc= w * srcImg.type;
    
    for (int j=0; j<nl; j++) {
        // get the address of row j
        uchar* dataIn= srcImg.pixels.ptr<uchar>(j);
        uchar* dataOut= srcImg.pixels.ptr<uchar>(j);
        for (int i=0; i<nc; i++) {
            
            //Simple fixed thresholding method
            float newPix = 0;
            if (dataIn[i] > 127)
            {
                newPix = 255;
            }
            
            dataOut[i]= newPix;
        }
    }
    
    /* TOCHECK: not working, for some reason..?!?!?!
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            int p = (srcImg.pixelAt(i, j) > 127) ? 255 : 0;
            dstImg.pixelWrite(i, j, p);
        }
    }
     */
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

