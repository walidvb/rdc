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
using namespace std;
using namespace cv;

class Homo
{
public:
    Homo();
    Homo(Size boardSize_);
    
    bool addImages(Mat* src, Mat* trg);             //<! adds a pair of images, directly translated into a set of point correspondences
    
    void computeHomo();                              //<! computes the homography matrix from all the points that were added via addImages, and its inverse
    void warp(Mat& img, Size size);                                //<! warps the captured image to the projectors' perspective

    Point getTargetPoint(int x, int y);       //<! used to retrieve point*homography
    Point getTargetPoint(const Point pos);    //<! used to retrieve point*homography
    Point getSourcePoint(int x, int y);
    Point getSourcePoint(const Point pos);
    
    //Getters
    Mat getHomo() const;                            //<! returns the homography matrix
    Mat getHomoInv() const;                         //<! returns the homography matrix inverse
    void setPattern(Image* pattern);                //<! sets the pattern projected used in the homography / unused
    
private:
    Size boardSize;                                 //<! size of the board used for the homography
    Point getPoint(int x, int y, Mat& h) ;
    Image* source;                                  //<! the source image used, the pattern in our case /unused
    Mat homo;                                       //<! the homography matrix
    Mat homoInv;                                    //<! the homography matrix inverse
    vector<Point2f> srcPoints;                      //<! the points found in the source image
    vector<Point2f> trgPoints;                      //<! the points found in the target image
};

#endif
