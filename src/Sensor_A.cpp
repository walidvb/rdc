//
//  Sensor_A.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#include "Sensor_A.h"
Sensor_A::Sensor_A() : width(800), height(600)
{
    frame = Image(width, height);
}

Sensor_A::Sensor_A(int width, int height) : width(width), height(height)
{
    frame = Image(width, height);
}

//Getters and Setters
int Sensor_A::getWidth() const
{
    return width;
}

int Sensor_A::getHeight() const
{
    return height;
}

