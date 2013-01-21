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

ci::Vec2f Renderer_Cinder::V2D2Vecf(V2D src) const
{
    ci::Vec2f dst( src.getX(), src.getY() );
    return dst;
}

void Renderer_Cinder::drawImg(const Image& img, int POS) const
{
    //Draw mode
    cv::imshow("", img.pixels);
    Channel32f chan(img.pixels.cols, img.pixels.rows);
    for(int i = 0; i < img.pixels.rows; i++)
    {
        for (int j = 0; j<img.pixels.cols; j++)
        {
            chan.setValue(ci::Vec2i(i, j), img.pixelAt(j, i));
        }
    }
    
    Texture myImg;
    myImg = Texture(chan);
    draw(myImg);
    //Verbose mode
//    
//    cout <<"=========================="<<endl;
//    for (int i = 0; i < img.width; i++) {
//        for (int j = 0; j < img.height; j++)
//        {
//            cout << img.pixelAt(i,j)<<" ";
//        }
//        cout<<endl;
//    }
}