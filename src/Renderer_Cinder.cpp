//
//  Renderer_Cinder.cpp
//  RDC
//
//  Created by Gaston on 11/21/12.
//
//

#include "Renderer_Cinder.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace gl;

Renderer_Cinder::Renderer_Cinder() : Renderer_A() {}
Renderer_Cinder::Renderer_Cinder(int w, int h):Renderer_A(w, h) {}

void Renderer_Cinder::drawRect(float topleft, float topright, float bottomright, float bottomleft ) const
{
    float r = 1;
    float g = 1;
    float b = 1;
    
    color(r, g, b);
    Rectf rect;
    drawSolidRect(rect);
}
