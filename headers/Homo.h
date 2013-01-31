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
    
    void addImages(Image src, Image trg);           //<! adds a pair of images, directly translated into a set of point correspondences 
    Mat computeHomo();                              //<! computes the homography matrix from all the points that were added via addImages, and returns it
    Point getTargetPoint(int x, int y) const;       //<! used to retrieve point*homography
    Point getTargetPoint(const Point pos) const;    //<! used to retrieve point*homography
    
    Size boardSize;                                 //<! size of the board used for the homography
    //Getters
    Mat getHomo();                                  //<! returns the homography matrix
    void setPattern(Image* pattern);                //<! sets the pattern projected used in the homography / unused
    
private:
    Image* source;                                  //<! the source image used, the pattern in our case /unused
    Mat homo;                                       //<! the homography matrix
    vector<Point2f> srcPoints;                      //<! the points found in the source image
    vector<Point2f> trgPoints;                      //<! the points found in the target image
};

#endif
