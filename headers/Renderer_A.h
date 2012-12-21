/*---------------------------------------------------------------
 
 Creation:	20.11.2012
 Description:		a renderer
 Children:          Renderer_Cinder
 Methodes:			Construct/Destruct
                    drawRect()
                    drawStripeVert(), drawStripeHorz()
                    
 ---------------------------------------------------------------*/

#ifndef RDC_Renderer_A_h
#define RDC_Renderer_A_h

#include "common.h"

class Renderer_A
{
public:
    Renderer_A();
    Renderer_A(int width, int height);
    //virtual void drawRect( V2D& topleft, V2D& topright, V2D& bottomright, V2D& bottomleft ) const = 0;
    virtual void drawRect( float& x1, float& y1, float& x2, float& y2 ) const = 0;
    virtual void drawImg(vector<float> img) const = 0;

    //void drawRect( V2D& topleft, V2D& bottomright ) const;
    void drawStripeVert(float& xOffset, float& width) const;
    void drawStripeHorz(float& yOffset, float& height) const;
    
    //Getters and Setters
    int getWidth() const;
    int getHeight() const;
    
    static const float X_ZERO;
    static const float Y_ZERO;
protected:
    int width, height;
};

#endif
