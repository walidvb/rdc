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
#include "Timer.h"

//Constructor
RDC::RDC(int width, int height, Timer* timer) : outWidth(width), outHeight(height), outSize(width, height), timer(timer){}


//Public methods

void RDC::init()
{
    homo = new Homo();
    isHomoComputed = false;
    isEMComputed = false;
    isFMComputed = false;
    isCalibrated = false;
    isEMRendered = false;
    isFMRendered = false;
    isColorCalibrated = false;
    timeToWait = 2;
    magicE = 1;
    magicR = 1;
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
    imwrite("/Users/Gaston/dev/RDC/tests/original.jpg", *R);
    //cout << "[RDC]: channels: [R:" << R->channels() << "], [EM:" << EM.channels() << "], [FM:" << FM.channels()<< "]" << endl;
    R->convertTo(*R, CV_64F);
    EM.convertTo(EM, CV_64F);
    FM.convertTo(FM, CV_64F);
    
    *R /= 255;
    EM /= 255;
    FM /= 255;
    
    double iMax;
    //obtain iterator at initial position
    cv::Mat_<cv::Vec3d>::iterator it=R->begin<cv::Vec3d>();
    cv::Mat_<cv::Vec3d>::iterator itend=R->end<cv::Vec3d>();
    for(iMax = 0; it != itend; it++)
    {
        iMax = std::max((*it)[0], iMax);
        iMax = std::max((*it)[1], iMax);
        iMax = std::max((*it)[2], iMax);
    }
    //cout << "[RDC] iMax beforeprocess:" << iMax;
    
    cv::subtract(*R*magicR, magicE*EM, *R);
    cv::divide(*R, FM, *R);  //commented to see smth.
    imwrite("/Users/Gaston/dev/RDC/tests/compensated.jpg", *R*255);
    *R *= 255;
    R->convertTo(*R, CV_8U);
    cout << "[RDC] image was compensated!" << endl;
}


void RDC::calibrateColors(Sensor* sensor, Renderer_A* gfx)
{
    isColorCalibrated = true;
    cout << "[RDC]: color calibration over" << endl;
}


void RDC::grabFM(Sensor *cam, Renderer_A *gfx)
{
    Mat plain_ = Mat::ones(outHeight, outWidth, CV_8U)*255;
    Image plain(plain_);
    //draw it
    gfx->drawImg(&plain);
    if(timer->hasElapsed(timeToWait))
    {
        cout << "grabbed FM" << endl;
        FM = cam->grabFrame().getMat()->clone();
        isFMComputed = true;
        timer->resetTimer();
    }
}

void RDC::grabEM(Sensor *cam, Renderer_A *gfx)
{
    Mat plain_ = Mat::zeros(outHeight, outWidth, CV_8U);
    Image plain(plain_);
    //draw it
    gfx->drawImg(&plain);
    if(timer->hasElapsed(timeToWait))
    {
        cout << "grabbed EM" << endl;
        EM = cam->grabFrame().getMat()->clone();
        isEMComputed = true;
        timer->resetTimer();
    }
}

void RDC::computeLighting()
{
    
    //compute homographies EM and FM images
    homo->warp(EM, outSize);
    imwrite("/Users/Gaston/dev/RDC/tests/EM.jpg", EM);
    
    homo->warp(FM, outSize);
    imwrite("/Users/Gaston/dev/RDC/tests/FM.jpg", FM);
    
    isCalibrated = true;
}

void RDC::grabAndSaveFrame(Sensor* cam)
{
    Mat picture = *cam->grabFrame().getMat();
    homo->warp(picture, outSize);
    imwrite("/Users/Gaston/dev/RDC/tests/result.jpg", picture);
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
        timer->resetTimer();
    }
    
}


//Getters & Setters

void RDC::setmagicE(double factor)
{
    magicE+=factor;
    magicE = (magicE < 0)? 0 : (magicE > 1) ? 1 : magicE;
    cout << "magicE: " << magicE << endl;
    
}
void RDC::setmagicR(double factor)
{
    magicR+=factor;
    magicR = (magicR < 0)? 0 : (magicR > 1) ? 1 : magicR;
}

bool RDC::getIsColorCalibrated()
{
    return isColorCalibrated;
}

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