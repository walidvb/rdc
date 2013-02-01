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

Image::Image(int width, int height, imgType type) : width(width), height(height), type(type)
{
    this->pixels = Mat(width, height, CV_8U);
    setup();
}

Image::Image(Mat img) : pixels(img)
{
    setup();
}

Image::Image(Image const& img)
{
    this->pixels = img.pixels;
    setup();
}

Image::Image(string path)
{
    load(path);
}

int Image::index(int x, int y, int w)
{
    
    return y*w+x;
}

//TODO change to template, as this should be able to return Vec3b too.
uchar Image::pixelAt(int x, int y) const
{
    uchar pix = pixels.ptr<uchar>(y)[x];
    return pix;
}

//TODO change to template, as this should be able to take as argument Vec3b too.
void Image::pixelWrite(uchar value, int x, int y)
{
    pixels.ptr<uchar>(y)[x] = value;
}
    
void Image::load(string filepath)
{
    pixels = imread(filepath);
    cout << pixels.channels() << endl;
    setup();
}


void Image::setup()
{
    if(pixels.channels() == 1)
    {
        type = IMG_GRAY;
    }
    else
    {
        type = IMG_CLR;
    }

    width = pixels.cols;
    height = pixels.rows;
}

//Getters
Mat Image::getPixels() const
{
    return pixels;
}

Image::imgType Image::getType() const
{
    return type;
}
int Image::getWidth() const
{
    return width;
}
int Image::getHeight() const
{
    return height;
}

//Setter
void Image::setPixels(Mat& mat)
{
    pixels = mat;
}
void Image::setType(Image::imgType type)
{
    this->type = type;
}
void Image::setWidth(int width)
{
    this->width = width;
}
void Image::setHeight(int height)
{
    this->height = height;
}
