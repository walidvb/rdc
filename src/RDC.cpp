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
    cout << "[RDC]: R.channels(): " << R->channels() << endl;
    R->convertTo(*R, CV_64F);
    result->convertTo(*result, CV_64F);
    EM.convertTo(EM, CV_64F);
    FM.convertTo(FM, CV_64F);
    
    *R /= 255;
    
    if(&srcImg != &dstImg)
    {
        //resize(*result, *result, out);    //resize the matrix to the size of the output
    }
    cv::subtract(*R, EM/255, *result);
    cv::divide(*result, FM/255, *result);  //commented to see smth.
    imwrite("/Users/Gaston/dev/RDC/tests/compensated_b4.jpg", *result*255);
    /*
     //divide channels and get max(r,g,b)
     vector<Mat> splitted;
     split(*result, splitted);
     Mat red = splitted[2];
     imwrite("/Users/Gaston/dev/RDC/tests/compensated_b4_red.jpg", red*255);
     Mat green = splitted[1];
     imwrite("/Users/Gaston/dev/RDC/tests/compensated_b4_green.jpg", green*255);
     Mat blue = splitted[0];
     imwrite("/Users/Gaston/dev/RDC/tests/compensated_b4_blue.jpg", blue*255);
     double rMax = *max_element(red.begin<double>(), red.end<double>());
     double gMax = *max_element(blue.begin<double>(), blue.end<double>());
     double bMax = *max_element(green.begin<double>(), green.end<double>());
     double iMax = max(rMax, gMax, bMax);
     
     cout << "[RDC] iMax:" << iMax << endl;
     *result /= iMax;
     */
    double iMax = 0;
    // obtain iterator at initial position
    cv::Mat_<cv::Vec3d>::iterator it=result->begin<cv::Vec3d>();
    cv::Mat_<cv::Vec3d>::iterator itend=result->end<cv::Vec3d>();
    for(; it != itend; it++)
    {
        iMax = std::max((*it)[0], iMax);
        iMax = std::max((*it)[1], iMax);
        iMax = std::max((*it)[2], iMax);
    }
    cout << "[RDC] iMax before:" << iMax;
    //-----------------------------------divide by iMax
    *result /= iMax;
    imwrite("/Users/Gaston/dev/RDC/tests/compensated_a4ter.jpg", *result);
    it=result->begin<cv::Vec3d>();
    iMax = 0;
    for(; it != itend; it++)
    {
        iMax = std::max((*it)[0], iMax);
        iMax = std::max((*it)[1], iMax);
        iMax = std::max((*it)[2], iMax);
    }
    cout << ", after/iMax: " << iMax;
    //-----------------------------------mult by 255
    
    *result *= 255;
    it=result->begin<cv::Vec3d>();
    iMax = 0;
    for(; it != itend; it++)
    {
        iMax = std::max((*it)[0], iMax);
        iMax = std::max((*it)[1], iMax);
        iMax = std::max((*it)[2], iMax);
    }
    cout << ", after/iMax*255: " << iMax;

    //-----------------------------------convert to CV_8U
    result->convertTo(*result, CV_8U);
    it=result->begin<cv::Vec3d>();
    itend=result->end<cv::Vec3d>();

    iMax = 0;
    it=result->begin<cv::Vec3d>();
    for(; it != itend; it++)
    {
        iMax = std::max((*it)[0], iMax);
        iMax = std::max((*it)[1], iMax);
        iMax = std::max((*it)[2], iMax);
    }
    cout << ", after/iMax*255.conv() before: " << iMax << endl;
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
    imwrite("/Users/Gaston/dev/RDC/tests/EM.jpg", EM);
    
    cv::warpPerspective(FM,                         // input image
                        FM,                         // output image
                        homo->getHomoInv(),         // homography
                        Size(outWidth,
                             outHeight));
    imwrite("/Users/Gaston/dev/RDC/tests/FM.jpg", FM);
    
    isCalibrated = true;
}

void RDC::grabAndSaveFrame(Sensor* cam)
{
    imwrite("/Users/Gaston/dev/RDC/tests/result.jpg", *cam->grabFrame().getMat());
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
