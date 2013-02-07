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

Image::Image(Image const& img, bool clone)
{
    if(clone)
    {
    this->pixels = img.pixels.clone();
    }
    else
    {
        this->pixels = img.pixels;
    }
    setup();
}

Image::Image(string path, bool grayscale)
{
    load(path, grayscale);
    cout << "creating image for " << path << "(channels: " << pixels.channels() << ", size[" << pixels.cols << " " << pixels.rows << "];" << endl;
}

int Image::index(int x, int y, int w)
{
    
    return y*w+x;
}

//TODO change to template, as this should be able to return Vec3b too.
Vec3b Image::pixelAt(int x, int y) const
{
    Vec3b pix = pixels.at<Vec3b>(y, x);
    return pix;
}

//TODO change to template, as this should be able to take as argument Vec3b too.
void Image::pixelWrite(Vec3b value, int x, int y)
{
    
    pixels.at<Vec3b>(y,x) = value;
}
    
void Image::load(string filepath, bool grayscale)
{
    if(grayscale)
    {
        pixels = imread(filepath, 0);
    }
    else
    {
        pixels = imread(filepath);
    }
    setup();
}

void Image::clone(Image& src)
{
    this->pixels = src.pixels.clone();
    setup();
}

void Image::resize(int maxHeight)
{
    this->resize(maxHeight*width/height, maxHeight);
}

void Image::resize(int width_, int height_)
{
    Size s(width_, height_);
    cv::resize(pixels, pixels, s);
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
Mat* Image::getMat()
{
    return &pixels;
}
vector<uchar> Image::getPixels()
{
    vector<uchar> pix;
    // number of lines
    int nl= height;
    // total number of elements per line
    int nc= width * type;
    
    for (int j=0; j<nl; j++)
    {
        // get the address of row j
        uchar* data= pixels.ptr<uchar>(j);
        for (int i=0; i<nc; i++)
        {
            pix.push_back(data[j]);
        }
    }
    return pix;

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
void Image::setMat(Mat& mat)
{
    pixels = mat;
}
void Image::setPixels(vector<uchar>&  pixels , int width, int height)
{
    Mat m(height, width, CV_8UC2, &pixels);
    this->pixels = m;
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
