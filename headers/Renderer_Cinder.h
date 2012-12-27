/*---------------------------------------------------------------
 
 Creation:	20.11.2012
 Description:		2 dimension vector class
 Superclass:        Renderer_A
 Methodes:			Construct/Destruct
                    drawRect()
 ---------------------------------------------------------------*/

#ifndef RDC_Renderer_Cinder_h
#define RDC_Renderer_Cinder_h

#include "Renderer_A.h"
#include "cinder/gl/gl.h"

using namespace ci;

class Renderer_Cinder : public Renderer_A
{
    
public:
    Renderer_Cinder();
    Renderer_Cinder(int width, int height);
    void drawRect( float& x1, float& y1, float& x2, float& y2 ) const;
    void drawImg(const Image& img, int POS) const;

private:
    Vec2f V2D2Vecf(V2D src) const;
    
};
#endif
