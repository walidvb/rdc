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
    //Constructors
    Image();
    Image(int width, int height);
    Image(Mat img);
    Image(Image const& img);
    Image(string path);
    
    //Methods
    float pixelAt(int x, int y) const;    //!< returns the pixel value at (x, y)
    void pixelWrite(float value, int x, int y); //!< writes value at pixel (x, y)
    
    void load(string filepath);         //<! used to load an image file. Supported formats are those of openCV
    //vector<float> Mat2Img(cv::Mat original); //<! translates an openCV Mat image into my vector<float> object.
    
    //Attributes
    Mat pixels;           //!< all pixels of the image
    int type;             //<! type of im   age: IMG_GRAY or IMG_CLR
    int width;            //<! the width of the image
    int height;           //<! the height of the image
    
    //Setter
    void setPixels(const Mat& src);

private:
    static int index(int x, int y, int w);    
    void setup();   //<! just a private function to keep everything in order
};


#endif
