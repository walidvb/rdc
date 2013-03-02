//
//  Renderer_CV.cc
//  RDC
//
//  Created by Gaston on 1/21/13.
//
//

#include "Renderer_CV.h"

Renderer_CV::Renderer_CV() : Renderer_A()
{
    
}

Renderer_CV::Renderer_CV(int width, int height) : Renderer_A(width, height)
{
    
}

void Renderer_CV::drawRect(float& x1, float& y1, float& x2, float& y2) const
{
    
}

void Renderer_CV::drawImg(Image* img) const
{
    //img->resize(600);
    string name = "Window ha!";
    namedWindow(name, WINDOW_NORMAL);
    //setWindowProperty(name, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    if(img->getMat()->empty())
    {
        cout << "[Renderer] Error! Could not read the image from disk";
        exit(-1);
    }
    imshow(name, (*img->getMat()));
    
    //waitKey(0);
    
    //destroyWindow(name);
}

void Renderer_CV::destroyImg(string name)
{
    destroyWindow(name);

}