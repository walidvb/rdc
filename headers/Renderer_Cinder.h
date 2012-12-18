//
//  Renderer_Cinder.h
//  RDC
//
//  Created by Gaston on 11/21/12.
//
//

#ifndef RDC_Renderer_Cinder_h
#define RDC_Renderer_Cinder_h

#include "Renderer_A.h"

class Renderer_Cinder : public Renderer_A
{
    
public:
    Renderer_Cinder();
    Renderer_Cinder(int width, int height);
    void drawRect(float topleft, float topright, float bottomright, float bottomleft ) const; 
    void drawStripeVert(float xOffset, float width) const;
    void drawStripeHorz(float yOffset, float height) const;

};
#endif
