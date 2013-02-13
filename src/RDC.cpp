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

void RDC::init(int resolution)
{
    resolution = resolution;
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
    
    //create black and white images. probably only white though, doesn't make too much sense to actually display black, rather display nothing
    Mat plain_ = Mat::ones(outHeight, outWidth, CV_8U)*255;
    Image plain(plain_);
    //draw it
    gfx->drawImg(&plain);
    //capture this into FM
    FM = *(cam->grabFrame().getMat());
    //do the same with black
    plain_ = Mat::zeros(outHeight, outWidth, CV_8U);
    plain.setMat(plain_); //probably not needed, as it points to the same Mat already, but for the heck of it
    gfx->drawImg(&plain);
    EM = *(cam->grabFrame().getMat());
    
    //get EM and FM matrices
    cv::warpPerspective(EM, // input image
                        EM,         // output image
                        homo->getHomoInv(),      // homography
                        Size(outWidth,
                             outHeight));
    cv::warpPerspective(FM, // input image
                        FM,         // output image
                        homo->getHomoInv(),      // homography
                        Size(outWidth,
                             outHeight));
}

void RDC::computeHomography(Sensor* cam, Renderer_A* gfx)
{
    //choose chessboard
    string chessboard;
    switch (resolution) {
        case p480:
            chessboard = "/Users/Gaston/dev/RDC/resources/chessboard480p.jpg";
            break;
        case p576:
            chessboard = "/Users/Gaston/dev/RDC/resources/chessboard576p.jpg";
            break;
        case p720:
            chessboard = "/Users/Gaston/dev/RDC/resources/chessboard720p.jpg";
            break;
        default:
            break;
    }
    
    Image chessboardPattern(chessboard, true);
    //project chessboard
    gfx->drawImg(&chessboardPattern);
    //capture it
    Image picture = cam->grabFrame();
    //add (chessboard, chessboard_capture) to homo
    homo->addImages(chessboardPattern.getMat(), picture.getMat());

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

//Getters

//Setters
