//
//  Renderer_A.cpp
//  RDC
//
//  Created by Gaston on 11/21/12.
//
//

#include "Renderer_A.h"

Renderer_A::Renderer_A(){}
Renderer_A::Renderer_A(int w, int h): width(w), height(h) {}

void Renderer_A::drawStripeVert(float xOffset, float width) const
{
    V2D topleft(xOffset, 0);
    V2D topright(xOffset + width, 0);
    V2D bottomleft(xOffset, this->height);
    V2D bottomright(xOffset + width, this->height);
    
    drawRect( topleft, topright, bottomright, bottomleft );
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
