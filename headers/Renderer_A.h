//
//  Renderer.h
//  RDC
//
//  Created by Gaston on 11/21/12.
//
//

#ifndef RDC_Renderer_A_h
#define RDC_Renderer_A_h

#include "common.h"

class Renderer_A
{
public:
    Renderer_A();
    Renderer_A(int width, int height);
    virtual void drawRect( V2D topleft, V2D topright, V2D bottomright, V2D bottomleft ) const = 0;

    void drawStripeVert(float xOffset, float width) const;
    void drawStripeHorz(float yOffset, float height) const;
    
    //Getters and Setters
    int getWidth() const;
    int getHeight() const;
    
protected:
    int width, height;
};

#endif
