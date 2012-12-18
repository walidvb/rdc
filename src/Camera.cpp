//
//  Camera.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#include "Camera.h"
Cam::Cam():Camera_A()
{
}

Cam::Cam(int width, int height):Camera_A(width,height)
{
    frame.resize(width*height);
}


void Cam::init()
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

vector<float> Cam::grabFrame()
{
    return frame;
}