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
#include "ColorCalibrator.h"

//Constructor
RDC::RDC(int width, int height, Timer* timer) : outWidth(width), outHeight(height), outSize(width, height), timer(timer){}


//Public methods

void RDC::init()
{
    homo = new Homo();
    colorCalib = new ColorCalibrator(homo, timer);
    isHomoComputed = false;
    isEMComputed = false;
    isFMComputed = false;
    isCalibrated = false;
    isEMRendered = false;
    isFMRendered = false;
    isFMMinComputed = false;
    isEMMaxComputed = false;
    isLightComputed = false;
    isFMMinEMMaxDone = false;
    isROIFMdone = false;
    isROIEMdone = false;
    timeToWait = 2;
    magicE = 1;
    magicR = 1;
    doAdapt = true;
    if(simu)    //image needs to be saved in the proper format, this might be an issue
    {
        EM = imread("/Users/Gaston/dev/RDC/tests/EM.jpg");
        FM = imread("/Users/Gaston/dev/RDC/tests/FM.jpg");
        EM.convertTo(EM, CV_64F);
        FM.convertTo(FM, CV_64F);
    }
}

void RDC::reinit()
{
    isHomoComputed = true;
    isEMComputed = false;
    isFMComputed = false;
    isCalibrated = false;
    isEMRendered = false;
    isFMRendered = false;
    isFMMinComputed = false;
    isEMMaxComputed = false;     //true because unused as of today.
    isLightComputed = false;
    isFMMinEMMaxDone = false;
    isROIFMdone = false;
    isROIEMdone = false;
    timeToWait = 2;
    magicE = 1;
    magicR = 1;
    doAdapt = true;

}

void RDC::setROI(int x1, int y1, int x2, int y2)
{
    
    int x1_ = min(x1, x2);
    int x2_ = max(x1, x2);
    int y1_ = min(y1, y2);
    int y2_ = max(y1, y2);
    if(isROIFMdone)
    {
        ROIFM[0] = x1_;
        ROIFM[1] = y1_;
        ROIFM[2] = x2_;
        ROIFM[3] = y2_;
        isROIFMdone = true;
    }
    else if(isROIFMdone)
    {
        ROIEM[0] = x1_;
        ROIEM[1] = y1_;
        ROIEM[2] = x2_;
        ROIEM[3] = y2_;
        isROIEMdone = true;
    }
}

void RDC::getFMMinEMMax()
{
    Mat* img;
    double* target;
    bool* currentChange;
    int ROICorners[4];
    if(!isFMMinComputed)
    {
        //cout << "[RDC]: getting FMMin..." << endl;
        img = &FM;
        target = &FMMin;
        currentChange = &isFMMinComputed;
    }
    else
    {
        //cout << "[RDC]. getting EMMax..." << endl;
        img = &EM;
        target = &EMMax;
        currentChange = &isEMMaxComputed;
        
    }
    
    if(isROIEMdone && isROIEMdone)
    {
        Mat ROI = (*img)(Range(ROICorners[2], ROICorners[3]), Range(ROICorners[0], ROICorners[1]));
        Scalar color = mean(ROI);
        double value = (color[0]+color[1]+color[2])/3;
        *target = value;
        *currentChange = true;
        cout << "[RDC]: FMMin: " << FMMin << " EMMax: " << EMMax << endl;
        isFMMinEMMaxDone = true;
        
    }
}

void RDC::adapt(Mat* pix)
{
    //pix € [0 1]
    if(isFMMinEMMaxDone)
    {
        //min + (value) * (max - min)
        double min, max;
        min = EMMax;
        max = FMMin;
        /* *pix += min;
         *pix *= max;*/
        *pix = min + *pix * (max - min);
    }
}

/*  The compensation algorithm goes like this:
 *   The image is altered by environment ligth(EM) and reflexivity of the surface(FM)
 *   in the following manner: R = I*FM+EM
 *   Compensated image can be found by solving I:I=(R-EM)/FM
 *   more info in the paper
 */

void RDC::compensate(Image* srcImg, Image* dstImg)
{
    Mat* R = srcImg->getMat();
    R->convertTo(*R, CV_64F);
    
    //preprocess the image
    if(doSmooth)
    {
        cv::medianBlur(*R, *R, smoothSize);
    }
    if(doAdapt)
    {
        adapt(R);
    }
    *R /= 255;
    cv::subtract(*R*magicR, EM*magicE, *R);
    cv::divide(*R, FM, *R);
    *R *= 255;
    R->convertTo(*R, CV_8U);
}


void RDC::calibrateColors(Sensor* sensor, Renderer_A* gfx)
{
    colorCalib->calibrate(sensor, gfx);
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
    homo->warp(FM, outSize);
    EM.convertTo(EM, CV_64F);
    FM.convertTo(FM, CV_64F);
    EM /= 255;
    FM /= 255;
    isLightComputed = true;
}

void RDC::grabAndSaveFrame(Sensor* cam)
{
    if(!simu)
    {
        Mat picture = *cam->grabFrame().getMat();
        homo->warp(picture, outSize);
        imwrite("~/Desktop/result.jpg", picture);
    }
}

void RDC::computeHomography(Sensor* cam, Renderer_A* gfx)
{
    string chessboard("/Users/Gaston/dev/RDC/resources/test.jpg");
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
}
void RDC::setmagicR(double factor)
{
    magicR+=factor;
    magicR = (magicR < 0)? 0 : (magicR > 1) ? 1 : magicR;    
}

bool RDC::getIsColorCalibrated()
{
    return colorCalib->getIsCalibrated();
}

void RDC::setSimu(bool simu)
{
    this->simu = simu;
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
bool RDC::getIsLightComputed()
{
    return isLightComputed;
}
bool RDC::getIsFMMinEMMaxDone()
{
    return isFMMinEMMaxDone;
}

void RDC::setIsEMRendered(bool isIt)
{
    isEMRendered = isIt;
}
void RDC::setIsFMRendered(bool isIt)
{
    isFMRendered = isIt;
}