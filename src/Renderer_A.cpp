//
//  Renderer_A.cpp
//  RDC
//
//  Created by Gaston on 11/21/12.
//
//

#include "Renderer_A.h"

const float Renderer_A::X_ZERO=0.0f;
const float Renderer_A::Y_ZERO=0.0f;

Renderer_A::Renderer_A(){}
Renderer_A::Renderer_A(int w, int h): width(w), height(h) {}

/*void Renderer_A::drawRect( V2D& topleft, V2D& bottomright ) const
{
    float x1 = topleft.getX();
    float y1 = topleft.getY();
    float x2 = bottomright.getX();
    float y2 = bottomright.getY();
    
    drawRect( x1, y1, x2, y2 );
}*/

void Renderer_A::drawStripeVert(float& xOffset, float& width_) const
{
    float y1 = Y_ZERO;
    float x2 = xOffset + width_;
    float y2 = (float)this->height;
    drawRect( xOffset, y1, x2 , y2 );
}

void Renderer_A::drawStripeHorz(float& yOffset, float& height_) const
{
    float x1 = X_ZERO;
    float x2 = (float)this->width;
    float y2 = yOffset + height_;

    drawRect( x1, yOffset, x2, y2 );
}

//Getters and Setters
int Renderer_A::getWidth() const
{
    return width;
}

int Renderer_A::getHeight() const
{
    return height;
}
