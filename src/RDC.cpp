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
    isFMMinComputed = false;
    isEMMaxComputed = false;
    isLightComputed = false;
    isFMMinEMMaxDone = false;
    hasNewROI = false;
    timeToWait = 2;
    magicE = 1;
    magicR = 1;
    if(simu)
    {
        EM = imread("/Users/Gaston/dev/RDC/tests/EM.jpg");
        FM = imread("/Users/Gaston/dev/RDC/tests/FM.jpg");
    }
}


void RDC::setROI(int x1, int y1, int x2, int y2)
{
    
    int x1_ = min(x1, x2);
    int x2_ = max(x1, x2);
    int y1_ = min(y1, y2);
    int y2_ = max(y1, y2);
    ROIStart[0] = x1_;
    ROIStart[1] = y1_;
    ROIEnd[0] = x2_;
    ROIEnd[1] = y2_;
    //cout << "[RDC]: ROI[" << ROIStart[0] << " - " << ROIEnd[0] << ", " << ROIStart[1] << " - " << ROIEnd[1] << "]" << endl;
    hasNewROI = true;
}

void RDC::getFMMinEMMax()
{
    Mat* img;
    double* target;
    bool* currentChange;
    if(!isFMMinComputed)
    {
        cout << "[RDC]: getting FMMin..." << endl;
        img = &FM;
        target = &FMMin;
        currentChange = &isFMMinComputed;
    }
    else
    {
        cout << "[RDC]. getting EMMax..." << endl;
        img = &EM;
        target = &EMMax;
        currentChange = &isEMMaxComputed;
        
    }
    
    if(hasNewROI)
    {
        Mat ROI = (*img)(Range(ROIStart[0], ROIEnd[0]), Range(ROIStart[1], ROIEnd[1]));
        hasNewROI = false;
        Scalar color = mean(ROI);
        cout << "[RDC]: Color selected: (" << color[0] << ", " << color[1] << ", " << color[2] << ")=" << color;
        
        double value = (color[0]+color[1]+color[2])/3;
        *target = value;
        *currentChange = true;
    }
    else
    {
        cout << "[RDC]: no ROI selected" << endl;
    }
    if(isFMMinComputed &&  isEMMaxComputed)
    {
        cout << "[RDC]: FMMin: " << FMMin << " EMMax: " << EMMax << endl;
        isFMMinEMMaxDone = true;
    }
}

void RDC::adapt(Mat* pix)
{
    //pix € [0 1]
    if(isFMMinEMMaxDone)
    {
        double min;
        min = FMMin;
        *pix *= min;
    }
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
    
    Mat* R = srcImg->getMat();
    
    imwrite("/Users/Gaston/dev/RDC/tests/original.jpg", *R);
    //cout << "[RDC]: type: [R:" << R->type() << "], [EM:" << EM.type() << "], [FM:" << FM.type()<< "]" << endl;
    R->convertTo(*R, CV_64F);
    //cout << "[RDC]: type: [R:" << R->type() << "]" << endl;
    imwrite("/Users/Gaston/dev/RDC/tests/original_.jpg", *R);
    
    //EM.convertTo(EM, CV_64F);
    //FM.convertTo(FM, CV_64F);
    adapt(R);
    
    *R /= 255;
    cv::subtract(*R*magicR, EM*magicE, *R);
    cv::divide(*R, FM, *R);
    
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
        imwrite("/Users/Gaston/dev/RDC/tests/result.jpg", picture);
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