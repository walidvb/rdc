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
    computeHomography(cam);//working
    computeLighting();//
}

void RDC::computeLighting()
{
    //TODO: remove that shit, and get real images from the sensor
    Image tmp_("/Users/Gaston/dev/RDC/resources/chesspic.jpg");
    Image tmp_2("/Users/Gaston/dev/RDC/resources/chesspic.jpg");
    
    //get EM and FM matrices
    cv::warpPerspective(*tmp_.getMat(), // input image
                        *EM.getMat(),         // output image
                        homo->getHomoInv(),      // homography
                        Size(outWidth,
                             outHeight));
    cv::warpPerspective(*tmp_2.getMat(), // input image
                        *FM.getMat(),         // output image
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

/*  The compensation algorithm goes like this:
 *   The image is altered by environment ligth(EM) and reflexivity of the surface(FM)
 *   in the following manner: R = I*FM+EM
 *   Compensated image can be found by solving I:I=(R-EM)/FM
 */
void RDC::compensate(Image* srcImg, Image* dstImg)
{
    Size originalSize(srcImg->getWidth(), srcImg->getHeight());
    
    Mat* R = srcImg->getMat();
    Mat* result = dstImg->getMat();
    Mat croppedEM = (*EM.getMat())(Rect(Point(0,0), R->size()));
    imshow("a4ter copy", croppedEM);
    waitKey(0);
    
    Size out(outWidth, outHeight);
    resize(*R, *R, out);    //resize the matrix to the size of the output
    
    if(srcImg != dstImg)
    {
        //resize(*result, *result, out);    //resize the matrix to the size of the output
    }
    cv::subtract(tmp, *EM.getMat(), tmp);
    //cv::divide(tmp, *FM.getMat(), *result);
    //resize(*result, *result, originalSize);
    cout << "image was compensated!" << endl;
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
