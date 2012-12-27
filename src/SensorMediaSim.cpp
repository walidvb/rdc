//
//  SensorMediaSim.cpp
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#include "SensorMediaSim.h"
#include "Tools.h"

SensorMediaSim::SensorMediaSim(int w, int h) : Sensor_A(w,h)
{
}

void SensorMediaSim::init()
{

}

Image SensorMediaSim::grabFrame()
{
    Image tmpImage(this->width, this->height);
    
    for (int i = 0; i < this->frame.width; i++) {
        for (int j = 0 ; j < this->frame.height; j++)
        {
            if(j%2==0)
            {
                tmpImage.pixelWrite(255, i, j);
            }
            else
            {
                tmpImage.pixelWrite(15, i, j);
            }
        }
    }
    return tmpImage;
}