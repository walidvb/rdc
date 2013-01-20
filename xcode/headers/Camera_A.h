//
//  Camera_A.h
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#ifndef RDC_Camera_A_h
#define RDC_Camera_A_h
#include "common.h"
class Camera_A
{
public:
    Camera_A();
    Camera_A(int width, int height);
    virtual void init() = 0;
    virtual vector<float> grabFrame() = 0;
    
    //Getters and Setters
    int getWidth() const;
    int getHeight() const;
    
protected:
    vector<float> frame;
    int width, height;
};


#endif
