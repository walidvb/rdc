//
//  SensorMediaSim.cpp
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#include "SensorMediaSim.h"
#include "Tools.h"
#include "cinder/Cinder.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Channel.h"

SensorMediaSim::SensorMediaSim(int w, int h) : Sensor_A(w,h)
{
}

void SensorMediaSim::init()
{
}

Image SensorMediaSim::grabFrame()
{
    ci::Url url( "http://testsite.onsport.com/wp-content/themes/onsport-jos/img/players/0601-090529lena512.bmp" );
    
    ci::Channel32f mChannel = ci::Channel32f( loadImage( loadUrl( url ) ) );
    Image tmpImage(mChannel.getWidth(), mChannel.getHeight());
    
    for (int i = 0; i < tmpImage.width; i++)
    {
        for (int j = 0 ; j < tmpImage.height; j++)
        {
            tmpImage.pixelWrite(*mChannel.getData(i, j), i, j);
        }
    }
    return tmpImage;
}