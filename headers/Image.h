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
    Image(Image const& img, bool clone = true);
    Image(string path, bool grayscale = false);
    
    //Methods
    Vec3b pixelAt(int x, int y) const;    //!< returns the pixel value at (x, y)
    void pixelWrite(Vec3b value, int x, int y); //!< writes value at pixel (x, y)
    
    void load(string filepath, bool grayscale = false);         //<! used to load an image file. Supported formats are those of openCV
    //vector<float> Mat2Img(cv::Mat original); //<! translates an openCV Mat image into my vector<float> object.
    void save(string filepath);                                 //<! saves an image to disk, in resourcePath
    void clone(Image& src);                  //<! clones src into caller
    //proc
    void resize(int maxHeight);
    void resize(int width_, int height_);
    
    //Getters
    Mat* getMat();                  //<! returns matrix address
    vector<uchar> getPixels() ;     //<! returns pixels as a vector, unused internally
    int getType() const;        //<! returns type of the matrix
    int getWidth() const;
    int getHeight() const;
    
    //Setter
    void setPixels(vector<uchar>&  pixels, int width, int height);
    void setMat(Mat& mat);
    void setType(int type);
    void setWidth(int width);
    void setHeight(int height);
    
    friend std::ostream& operator<<(std::ostream& o, const Image& img);   //<! couts width, height, type
    
private:
    static int index(int x, int y, int w);    
    void setup();   //<! just a private function to keep everything in order
    
    //Attributes
    Mat pixels;           //!< all pixels of the image
    int type;             //<! type of im   age: IMG_GRAY or IMG_CLR
    int width;            //<! the width of the image
    int height;           //<! the height of the image
};


#endif
