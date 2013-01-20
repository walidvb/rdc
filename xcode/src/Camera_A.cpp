//
//  Camera_A.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#include "Camera_A.h"
Camera_A::Camera_A():width(800),height(600)
{
    
}
Camera_A::Camera_A(int width, int height):width(width),height(height)
{

}

//Getters and Setters
int Camera_A::getWidth() const
{
    return width;
}

int Camera_A::getHeight() const
{
    return height;
}

