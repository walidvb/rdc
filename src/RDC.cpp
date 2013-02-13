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
    Mat croppedEM = EM(Rect(Point(0,0), R->size()));
    
    if(srcImg != dstImg)
    {
        //resize(*result, *result, out);    //resize the matrix to the size of the output
    }
    cv::subtract(*R, croppedEM, *result);
    //cv::divide(*result, croppedFM, *result);  //commented to see smth.
    cout << "image was compensated!" << endl;
}

//Private methods
void RDC::calibrateSystem(Sensor* cam, Renderer_A* gfx)
{
    //TODO: actually calibrate the camera(not needed for colorimetry)
    //TODO: add images to the homography
    computeHomography(cam, gfx);//working
    computeLighting(cam , gfx);//
}

void RDC::computeLighting(Sensor* cam, Renderer_A* gfx)
{
    //TODO: remove that shit, and get real images from the sensor
    Image tmp_("/Users/Gaston/dev/RDC/resources/chesspic.jpg");
    Image tmp_2("/Users/Gaston/dev/RDC/resources/chesspic.jpg");
    
    //get EM and FM matrices
    cv::warpPerspective(*tmp_.getMat(), // input image
                        EM,         // output image
                        homo->getHomoInv(),      // homography
                        Size(outWidth,
                             outHeight));
    cv::warpPerspective(*tmp_2.getMat(), // input image
                        FM,         // output image
                        homo->getHomoInv(),      // homography
                        Size(outWidth,
                             outHeight));
    //getSurface(&FM, &FM);
}

void RDC::computeHomography(Sensor* cam, Renderer_A* gfx)
{
    Image  im1("/Users/Gaston/dev/RDC/resources/chessboard65.jpg", true);
    Image im2("/Users/Gaston/dev/RDC/resources/chesspic.jpg", true);
    
    //project chessboard

    //capture it
    
    //add (chessboard, chessboard_capture) to homo
    
    homo->addImages(im1.getMat(), im2.getMat());

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



void RDC::getSurface(Image* source, Image* target)
{
    int outWidth = source->getWidth();
    int outHeight = source->getHeight();
    cout << outWidth << "," << outHeight << endl;
    Image tmp(outWidth, outHeight);
    cv::warpPerspective(*source->getMat(), // input image
                        *tmp.getMat(),         // output image
                        homo->getHomoInv(),      // homography
                        Size(outWidth,
                             outHeight));
    
    target->setMat(*tmp.getMat());
}

//Getters

//Setters
