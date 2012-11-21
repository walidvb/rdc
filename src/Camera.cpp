//
//  Camera.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#include "Camera.h"
Camera::Camera():Camera_A()
{
}

Camera::Camera(int width, int height):Camera_A(width,height)
{
    frame.resize(width*height);
}


void Camera::init()
{
    frame.resize(width*height);//allocation

    cout << "Camera init()" << endl;
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            frame[Tools::index(i, j, width)] = i*j/3.0f; //mock image :)
        }
    }
}

vector<float> Camera::grabFrame()
{
    return frame;
}