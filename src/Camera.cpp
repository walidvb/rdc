//
//  Camera.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#include "Camera.h"
Cam::Cam() :Camera_A()
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
    frame = chan2floats(loadFakeFrame());
}

vector<float> Cam::grabFrame()
{
    return frame;
}

int Cam::getFrameCount() const
{
    return frameCount;
}

vector<float> Cam::chan2floats(Channel32f channel)
{
    vector<float> floats;
    for(int y = 0; y < channel.getHeight(); ++y)
    {
        for(int x = 0; x < channel.getWidth(); ++x)
        {
            floats[Tools::index(x, y, width)] = *channel.getData(x, y);
        }
    }
    return floats;
}

Channel32f Cam::loadFakeFrame()
{
    Channel32f frame = Channel32f( loadImage( loadUrl( "pattern/horizontal/i1.png" ) ) );
    return frame;
}