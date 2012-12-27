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


class Image{
public:
    //Constructors
    Image();
    Image(int width, int height);
    Image(Image const& img);
    
    //Methods
    float pixelAt(int x, int y) const;    //!< returns the pixel value at (x, y)
    void pixelWrite(float value, int x, int y); //!< writes value at pixel (x, y)
    
    //Attributes
    vector<float> pixels; //!< list of all pixels of the frame
    int width;
    int height;

    
    static int index(int x, int y, int w);

private:
    
    
};


#endif
