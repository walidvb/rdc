//
//  Homo.h
//  RDC
//
//  Created by Gaston on 1/29/13.
//
//

#ifndef RDC_Homo_h
#define RDC_Homo_h

#include "common.h"

class Homo
{
public:
    Homo();
    Homo(cv::Size boardSize_);
    
    bool addImages(cv::Mat* src, cv::Mat* trg);             //<! adds a pair of images, directly translated into a set of point correspondences
    
    void computeHomo();                              //<! computes the homography matrix from all the points that were added via addImages, and its inverse
    void warp(cv::Mat& img, cv::Size size);                                //<! warps the captured image to the projectors' perspective
    void warp(Image& img, cv::Size size);                                //<! warps the captured image to the projectors' perspective

    cv::Point getTargetPoint(int x, int y);       //<! used to retrieve point*homography
    cv::Point getTargetPoint(const cv::Point pos);    //<! used to retrieve point*homography
    cv::Point getSourcePoint(int x, int y);
    cv::Point getSourcePoint(const cv::Point pos);
    
    //Getters
    cv::Mat getHomo() const;                            //<! returns the homography matrix
    cv::Mat getHomoInv() const;                         //<! returns the homography matrix inverse
    void setPattern(Image* pattern);                //<! sets the pattern projected used in the homography / unused
    
private:
    cv::Size boardSize;                                 //<! size of the board used for the homography
    cv::Point getPoint(int x, int y, cv::Mat& h) ;
    Image* source;                                  //<! the source image used, the pattern in our case /unused
    cv::Mat homo;                                       //<! the homography matrix
    cv::Mat homoInv;                                    //<! the homography matrix inverse
    std::vector<cv::Point2f> srcPoints;                      //<! the points found in the source image
    std::vector<cv::Point2f> trgPoints;                      //<! the points found in the target image
};

#endif
