//
//  Image.cpp
//  RDC
//
//  Created by Gaston on 12/27/12.
//
//

#define IMG_CLR 0
#define IMG_GRAY 1

#include "Image.h"
using namespace cv;

Image::Image()
{
    
}

Image::Image(int width, int height) : width(width), height(height)
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


float Image::pixelAt(int x, int y) const
{
    float pix = pixels.at<uchar>(y, x);
    return pix;
}

void Image::pixelWrite(float value, int x, int y)
{
    pixels.at<uchar>(y, x) = value;
}

void Image::load(string filepath)
{
    pixels = imread(filepath);
    setup();
}

void Image::setPixels(const cv::Mat &src)
{
    pixels = src.clone();
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