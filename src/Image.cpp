//
//  Image.cpp
//  RDC
//
//  Created by Gaston on 12/27/12.
//
//

#include "Image.h"


Image::Image()
{
    
}

Image::Image(int width, int height) : width(width), height(height)
{
    this->pixels = vector<float>(width*height);
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
    float pix = pixels[index(x, y, width)];
    return pix;
}

void Image::pixelWrite(float value, int x, int y)
{
    pixels[index(x, y, width)] = value;
}
