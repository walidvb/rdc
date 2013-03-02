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
    this->resolution = resolution;
    homo = new Homo();
    isHomoComputed = false;
    isEMComputed = false;
    isFMComputed = false;
    isCalibrated = false;
    isEMRendered = false;
    isFMRendered = false;
}

/*  The compensation algorithm goes like this:
 *   The image is altered by environment ligth(EM) and reflexivity of the surface(FM)
 *   in the following manner: R = I*FM+EM
 *   Compensated image can be found by solving I:I=(R-EM)/FM
 */
void RDC::compensate(Image* srcImg, Image* dstImg)
{
    if (EM.empty() || FM.empty()) {
        cerr << "[RDC] Compensation matrices have not been initialized, please run calibrateSystem" << endl;
        exit(-1);
    }
    Size originalSize(srcImg->getWidth(), srcImg->getHeight());
    
    Mat* R = srcImg->getMat();
    Mat* result = dstImg->getMat();
    *result /= 255;
    Mat croppedEM = EM(Rect(Point(0,0), R->size()))/255;
    Mat croppedFM = FM/255;
    
    if(srcImg != dstImg)
    {
        //resize(*result, *result, out);    //resize the matrix to the size of the output
    }
    cv::subtract(*R, croppedEM, *result);
    cv::divide(*result, croppedFM, *result);  //commented to see smth.
    *result *= 255;
    imwrite("/Users/Gaston/dev/RDC/tests/result.jpg", *result);

    cout << "[RDC] image was compensated!" << endl;
}

void RDC::grabFM(Sensor *cam, Renderer_A *gfx)
{
    Mat plain_ = Mat::ones(outHeight, outWidth, CV_8U)*255;
    Image plain(plain_);
    //draw it
    gfx->drawImg(&plain);
    if(isFMRendered)
    {
        FM = cam->grabFrame().getMat()->clone();
        imwrite("/Users/Gaston/dev/RDC/tests/FM_before.jpg", FM);

        isFMComputed = true;
    }
}

void RDC::grabEM(Sensor *cam, Renderer_A *gfx)
{
    Mat plain_ = Mat::zeros(outHeight, outWidth, CV_8U);
    Image plain(plain_);
    //draw it
    gfx->drawImg(&plain);
    if(isEMRendered)
    {
        EM = cam->grabFrame().getMat()->clone();
        isEMComputed = true;
    }
}

void RDC::computeLighting()
{
    imwrite("/Users/Gaston/dev/RDC/tests/FM.jpg", FM);
    imwrite("/Users/Gaston/dev/RDC/tests/EM.jpg", EM);

    //compute homographies EM and FM images
    cv::warpPerspective(EM,                         // input image
                        EM,                         // output image
                        homo->getHomoInv(),         // homography
                        Size(outWidth,
                             outHeight));
    imwrite("/Users/Gaston/dev/RDC/tests/EM_warp.jpg", EM);

    cv::warpPerspective(FM,                         // input image
                        FM,                         // output image
                        homo->getHomoInv(),         // homography
                        Size(outWidth,
                             outHeight));
    imwrite("/Users/Gaston/dev/RDC/tests/FM_warp.jpg", FM);

    isCalibrated = true;
}

void RDC::computeHomography(Sensor* cam, Renderer_A* gfx)
{
    //choose chessboard
    string chessboard;
    /*switch (resolution) {
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
     */
    chessboard = "/Users/Gaston/dev/RDC/resources/test.jpg";
    bool isGrayScale = false;
    Image chessboardPattern(chessboard, isGrayScale);
    Image picture;
    chessboardPattern.resize(outWidth, outHeight);
    gfx->drawImg(&chessboardPattern);
    picture = cam->grabFrame();
    
    if(homo->addImages(chessboardPattern.getMat(), picture.getMat()))
    {
        homo->computeHomo();
        isHomoComputed = true;
    }

}
//Getters & Setters

bool RDC::getIsHomoComputed()
{
    return isHomoComputed;
}
bool RDC::getIsEMComputed()
{
    return isEMComputed;
}
bool RDC::getIsFMComputed()
{
    return isFMComputed;
}
bool RDC::getIsCalibrated()
{
    return isCalibrated;
}
bool RDC::getIsEMRendered()
{
    return isEMRendered;
}
bool RDC::getIsFMRendered()
{
    return isFMRendered;
}

void RDC::setIsEMRendered(bool isIt)
{
    isEMRendered = isIt;
}
void RDC::setIsFMRendered(bool isIt)
{
    isFMRendered = isIt;
}
