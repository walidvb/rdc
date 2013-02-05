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

void Renderer_CV::drawImg(const Image& img, int POS) const
{
    Image display(img);
    display.resize(600);
    string name = "Window " + POS;
    namedWindow(name);
    imshow(name, display.getMat());
    
    waitKey(0);
    
    cvDestroyWindow("Display window");
    cout << "application ended: merci au revoir" << endl;
}
