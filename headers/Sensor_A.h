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
class Sensor_A
{
public:
    Sensor_A();
    Sensor_A(int width, int height);
    virtual void init() = 0;
    virtual Image grabFrame() = 0;
    
    //Getters and Setters
    int getWidth() const;
    int getHeight() const;
    
protected:
    Image frame;
    int width;
    int height;
};


#endif
