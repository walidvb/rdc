//
//  RDC.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//
#include "Sensor.h"
#include "Renderer_A.h"
#include "Homo.h"
#include "RDC.h"

//Public methods

void RDC::init()
{
    homo = new Homo();
}
void RDC::calibrate(Sensor* cam, Renderer_A* gfx)
{
    Image img = cam->grabFrame();
    cout << "Camera pixels:" << endl;
    /*
     for (int i = 0; i < cam->getWidth(); i++)
     {
     for (int j = 0; j < cam->getHeight(); j++)
     {
     cout << img.pixelAt(i, j) << " ";
     }
     cout << endl;
     }
     */
    projectStructuredLights(gfx);
    
    //TODO compute compensation matrix
}

void RDC::computeHomography(Sensor* cam, Renderer_A* gfx)
{
    //project pattern
    //capture pattern
    Image pattern = cam->grabFrame();
    //add them to our Homo object
    homo->addImages(pattern, pattern);
    
    //compute the homography matrix
    homo->computeHomo();
    
    int height = gfx->getHeight();
    int width = gfx->getWidth();
    
    //TODO: fill a mapping matrix rather than getPoint for each pixel? Probably best way to go
    camera2proj.create(height, width, CV_32FC2);   //CV_32FC2 for 2 channels of Point2f
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //set Mat[x][y] to the corresponding point
        }
    }
}

void RDC::compensate(Image& srcImg, Image& dstImg)
{
    int w = srcImg.getWidth();
    int h = srcImg.getHeight();
    int chan = srcImg.getType();
    
    //make sure dst is the correct size
    dstImg.getMat().create(h, w, srcImg.getMat().type());
    /*
    // number of lines
    int nl= h;
    // total number of elements per line
    int nc= w * srcImg.getType();
    
    for (int j=0; j<nl; j++) {
        // get the address of row j
        uchar* dataIn= srcImg.getMat().ptr<uchar>(j);
        uchar* dataOut= srcImg.getMat().ptr<uchar>(j);
        for (int i=0; i<nc; i++) {
            
            //Simple fixed thresholding method
            uchar newPix = 0;
            if (dataIn[i] > 127)
            {
                newPix = 255;
            }
            dataOut[i]= newPix;
        }
    }
     */
    bool d(true);
    for(int i = 0; i < w; i+=chan)
    {
        for(int j = 0; j < h; j+=chan)
        {

            uchar v = srcImg.pixelAt(i, j) > 127 ? 255 : 0;
            if(d){cout << v << endl; d = !d;}
            dstImg.pixelWrite(v, i, j);
        }
        
    }
    //TODO compensate #1 test with dummy matrix
}

//Private methods
void RDC::projectStructuredLights(Renderer_A* gfx)
{
    float xOffset = 20.0;
    float width_ = 20.0;
    gfx->drawStripeVert(xOffset, width_);
}

void RDC::getSurface(const Image* source, Image* target)
{
    for(int i = 0; i < target->getWidth(); i++)
    {
        for(int j = 0; j < target->getHeight(); j++)
        {
            Point2f loc = homo->getSourcePoint(i, j);
            target->pixelWrite(source->pixelAt(loc.x, loc.y), i, j);
        }
    }
}

void RDC::computeFM(const Image* FM)
{
    getSurface(FM, &this->FM);
}

