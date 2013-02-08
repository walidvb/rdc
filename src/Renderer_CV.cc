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

void Renderer_CV::drawImg(Image* img, int POS) const
{
    //display.resize(600);
    string name = "Window " + POS;
    namedWindow(name);
    imshow(name, (*img->getMat()));
    
    waitKey(0);
    
    cvDestroyWindow("Display window");
    cout << "application ended: merci au revoir" << endl;
}
