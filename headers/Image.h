//
//  Image.h
//  RDC
//
//  Created by Gaston on 12/27/12.
//  A Simple image class used along the whole process. Was created
//

#ifndef RDC_Image_h
#define RDC_Image_h

#include "common.h"
#include "Tools.h"
#include <opencv2/opencv.hpp>

using namespace cv;

class Image{
    
    
public:
    enum imgType {IMG_CLR = 3, IMG_GRAY = 1};   //<! the different types of image we can have. represents the number of channels, actually

    //Constructors
    Image();
    Image(int width, int height, imgType = IMG_GRAY);
    Image(Mat img);
    Image(Image const& img);
    Image(string path);
    
    //Methods
    uchar pixelAt(int x, int y) const;    //!< returns the pixel value at (x, y)
    void pixelWrite(uchar value, int x, int y); //!< writes value at pixel (x, y)
    
    void load(string filepath);         //<! used to load an image file. Supported formats are those of openCV
    //vector<float> Mat2Img(cv::Mat original); //<! translates an openCV Mat image into my vector<float> object.
    

    
    //Getters
    Mat getPixels() const;
    imgType getType() const;
    int getWidth() const;
    int getHeight() const;
    
    //Setter
    void setPixels(Mat& mat);
    void setType(Image::imgType type);
    void setWidth(int width);
    void setHeight(int height);

private:
    static int index(int x, int y, int w);    
    void setup();   //<! just a private function to keep everything in order
    
    //Attributes
    Mat pixels;           //!< all pixels of the image
    imgType type;             //<! type of im   age: IMG_GRAY or IMG_CLR
    int width;            //<! the width of the image
    int height;           //<! the height of the image
};


#endif
