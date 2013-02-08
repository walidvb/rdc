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

enum { FULL=0, ONE=1, TWO=2, THREE=3, FOUR=4 };

class Renderer_A
{
public:
    Renderer_A();
    Renderer_A(int width, int height);
    virtual ~Renderer_A(){}
    virtual void drawImg(Image* img, int POS) const = 0;
    
    //void drawRect( V2D& topleft, V2D& bottomright ) const;
    void drawStripeVert(float xOffset, float width) const;
    void drawStripeHorz(float yOffset, float height) const;
    
    //Getters and Setters
    int getWidth() const;
    int getHeight() const;
    
    static const float X_ZERO;
    static const float Y_ZERO;
    
protected:
    virtual void drawRect( float& x1, float& y1, float& x2, float& y2 ) const = 0;
    int width, height;
};

#endif
