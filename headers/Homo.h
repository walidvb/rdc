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
    
    void getHomography(Image* src, Image* dest);
    Point getPoint(int x, int y);    //<! used to retrieve point*homography
    void drawPointOnBoth(Point pos);    //<! used to draw points on both images, purely for testing purposes
    
    //Getters
    Mat getHomo();
    void setPattern(Image* pattern);
    
private:
    Image* source; //<! the source image used, the pattern in our case
    Mat homo;       //<! the homography matrix
};

#endif
