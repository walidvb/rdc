//
//  Image.cpp
//  RDC
//
//  Created by Gaston on 12/27/12.
//
//

#include "Image.h"
using namespace cv;

Image::Image()
{
    
}

Image::Image(int width, int height) : width(width), height(height)
{
    this->pixels = Mat(width, height, CV_8U);
}

Image::Image(Mat img) : pixels(img)
{
    width = img.cols;
    height = img.rows;
}

Image::Image(Image const& img)
{
    this->width = img.width;
    this->height = img.height;
    this->pixels = img.pixels;
}


int Image::index(int x, int y, int w)
{
    
    return y*w+x;
}


float Image::pixelAt(int x, int y) const
{
    float pix = pixels.at<uint8_t>(x, y);
    return pix;
}

void Image::pixelWrite(float value, int x, int y)
{
    pixels.at<uint8_t>(x, y) = value;
}
