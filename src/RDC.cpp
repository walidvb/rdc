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

//Constructor
RDC::RDC(int width, int height) : outWidth(width), outHeight(height){}


//Public methods

void RDC::init()
{
    homo = new Homo();
}
void RDC::calibrate(Sensor* cam, Renderer_A* gfx)
{
    Image img = cam->grabFrame();
    /*
    cout << "Camera pixels:" << endl;
    
     for (int i = 0; i < cam->getWidth(); i++)
     {
     for (int j = 0; j < cam->getHeight(); j++)
     {
     cout << img.pixelAt(i, j) << " ";
     }
     cout << endl;
     }
     */
    //TODO: add images to the homography
    projectPatterns(gfx);//TOCHECK: for the moment simply takes stills and adds them to the homo object
    computeHomography(cam);
    computeLighting();
}

void RDC::computeLighting()
{
    //TODO: remove that shit
    Image tmp_("/Users/Gaston/dev/RDC/resources/chesspic.jpg");
    cv::warpPerspective(*tmp_.getMat(), // input image
                        *EM.getMat(),         // output image
                        homo->getHomoInv(),      // homography
                        Size(outWidth,
                             outHeight));
    //getSurface(&FM, &FM);
}

void RDC::computeHomography(Sensor* cam)
{
    //project pattern
    //capture pattern
    //Image pattern = cam->grabFrame();
    //add them to our Homo object
    //homo->addImages(pattern, pattern);
    
    //compute the homography matrix
    homo->computeHomo();
    
    /*
    //TODO: fill a mapping matrix rather than getPoint for each pixel? Probably best way to go
    camera2proj.create(height, width, CV_32FC2);   //CV_32FC2 for 2 channels of Point2f
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //set Mat[x][y] to the corresponding point
        }
    }
    */
}

void RDC::compensate(Image& srcImg, Image& dstImg)
{
    int w = srcImg.getWidth();
    int h = srcImg.getHeight();
    int chan = srcImg.getType();
    
    //make sure dst is the correct size
    dstImg.getMat()->create(outHeight, outWidth, srcImg.getMat()->type());
    for(int i = 0; i < w*chan; i+=1)
    {
        for(int j = 0; j < h; j+=1)
        {

            Vec3b v = srcImg.pixelAt(i, j);
            //TODO compensat v according to EM and FM
            dstImg.pixelWrite(v, i, j);
        }
        
    }
    //TODO compensate #1 test with dummy matrix
}

//Private methods
void RDC::projectPatterns(Renderer_A* gfx)
{
    float xOffset = 20.0;
    float width_ = 20.0;
    gfx->drawStripeVert(xOffset, width_);
    Image  im1("/Users/Gaston/dev/RDC/resources/chessboard65.jpg", true);
    Image im2("/Users/Gaston/dev/RDC/resources/chesspic.jpg", true);

    homo->addImages(im1.getMat(), im2.getMat());
}

void RDC::getSurface(Image* source, Image* target)
{
    int outWidth = source->getWidth();
    int outHeight = source->getHeight();
    cout << outWidth << "," << outHeight << endl;
    Image tmp(outWidth, outHeight);
    cout << "tmp: " << tmp << endl;
    
    //TOCHECK: probably not too efficient, but ill go with that for the moment...
    /*for(int i = 0; i < outWidth; i++)
    {
        for(int j = 0; j < outHeight; j++)
        {
            Point2f loc = homo->getTargetPoint(i, j);
            tmp.pixelWrite(source->pixelAt(i, j), i, j);
        }
    }
    */
    cv::warpPerspective(*source->getMat(), // input image
                        *tmp.getMat(),         // output image
                        homo->getHomoInv(),      // homography
                        Size(outWidth,
                             outHeight));

    target->setMat(*tmp.getMat());
}

//Getters

Image* RDC::getEM()
{
    return &EM;
}
//Setters
