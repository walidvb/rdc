//
//  SensorSimera.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#include "SensorSim.h"
SensorSim::SensorSim() :Sensor_A()
{
}

SensorSim::SensorSim(int width, int height):Sensor_A(width,height)
{
    frame.pixels.resize(width*height);
}


void SensorSim::init()
{
    frame.pixels.resize(width*height);//allocation

cout << "SensorSim init()" << endl;
    frame = chan2floats(loadFakeFrame());
}

Image SensorSim::grabFrame()
{
    return frame;
}

int SensorSim::getFrameCount() const
{
    return frameCount;
}

Image SensorSim::chan2floats(Channel32f channel)
{
    Image tmpImg(channel.getWidth(), channel.getHeight());
    
    for(int y = 0; y < channel.getHeight(); ++y)
    {
        for(int x = 0; x < channel.getWidth(); ++x)
        {
            tmpImg.pixelWrite(*channel.getData(x, y), x, y);
        }
    }
    return tmpImg;
}

Channel32f SensorSim::loadFakeFrame()
{
    Channel32f frame = Channel32f( loadImage( loadUrl( "pattern/horizontal/i1.png" ) ) );
    return frame;
}