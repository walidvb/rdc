//
//  Camera.h
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//

#ifndef RDC_Camera_h
#define RDC_Camera_h

#include "Camera_A.h"

class Cam : public Camera_A
{
public:
    Cam();
    Cam(int width, int height);
    void init();
    vector<float> grabFrame();
};

#endif
