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

SensorMediaSim::SensorMediaSim() : Sensor_A() {}

SensorMediaSim::SensorMediaSim(int w, int h) : Sensor_A(w,h) {}

string SensorMediaSim::init(string filepath)
{
    Mat img = imread(filepath);
    Image tmpImage(img);
    width = tmpImage.width;
    height = tmpImage.height;
    frame = tmpImage;
    return filepath;
}

Image SensorMediaSim::grabFrame()
{

    //read file
    //Create image
    
    return frame;
}