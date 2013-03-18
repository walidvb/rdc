//
//  Renderer_CV.h
//  RDC
//
//  Created by Gaston on 1/21/13.
//
//

#ifndef RDC_Renderer_CV_h
#define RDC_Renderer_CV_h

#include "common.h"
#include "Renderer_A.h"

using namespace cv;

class Renderer_CV : public Renderer_A
{
    
public:
    Renderer_CV();
    Renderer_CV(int width, int height);
    void drawRect( float& x1, float& y1, float& x2, float& y2 ) const;
    void drawImg(Image* img) const;
    void destroyImg(string name);
    
private:    
};

#endif
