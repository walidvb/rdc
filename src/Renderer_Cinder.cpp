//
//  Renderer_Cinder.cpp
//  RDC
//
//  Created by Gaston on 11/21/12.
//
//

#include "Renderer_Cinder.h"
#include "common.h"

using namespace gl;

Renderer_Cinder::Renderer_Cinder() : Renderer_A() {}
Renderer_Cinder::Renderer_Cinder(int& w, int& h):Renderer_A(w, h) {}

void Renderer_Cinder::drawRect( float& x1, float& y1, float& x2, float& y2 ) const
{
    float r = 1;
    float g = 1;
    float b = 1;
    
    color(r, g, b);
    
    Rectf rect( x1, y1, x2, y2 );
    drawSolidRect(rect);
}

Vec2f Renderer_Cinder::V2D2Vecf(V2D src) const
{
    Vec2f dst( src.getX(), src.getY() );
    return dst;
}

void Renderer_Cinder::drawImg(vector<float> img) const
{
    //TODO
}