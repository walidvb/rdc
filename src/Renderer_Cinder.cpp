//
//  Renderer_Cinder.cpp
//  RDC
//
//  Created by Gaston on 11/21/12.
//
//

#include "Renderer_Cinder.h"
#include "common.h"
#include "cinder/Channel.h"
#include "cinder/gl/Texture.h"

using namespace gl;

Renderer_Cinder::Renderer_Cinder() : Renderer_A() {}
Renderer_Cinder::Renderer_Cinder(int w, int h):Renderer_A(w, h) {}

void Renderer_Cinder::drawRect( float& x1, float& y1, float& x2, float& y2 ) const
{
    float r = 1;
    float g = 1;
    float b = 1;
    
    color(r, g, b);
    
    Rectf rect( x1, y1, x2, y2 );
    drawSolidRect(rect);
}



void Renderer_Cinder::drawImg(Image* img) const
{    
    int w = img->getWidth();
    int h = img->getHeight();

    //conversion from cv::mat to ci::surface
    ci::Surface8u surface(w, h, false);
    for(int i = 0; i < w; i+=1)
    {
        for (int j = 0; j<h; j+=1)
        {
            cv::Vec3b pixel = img->pixelAt(i,j);
            unsigned char b = pixel[0];
            unsigned char g = pixel[1];
            unsigned char r = pixel[2];
            cinder::Vec2i pos(i,j);
            ci::ColorT<unsigned char> color(r,g,b);
            surface.setPixel(pos, color);
        }
    }
    
    ci::gl::Texture myImg;
    //give surface to texture
    myImg = ci::gl::Texture(surface);
    ci::gl::draw(myImg);
}

void Renderer_Cinder::clear() const
{
    ci::gl::clear( ci::Color( 0, 0, 0 ) );
}

void Renderer_Cinder::setFullscreen(bool isFullscreen)
{
    
}