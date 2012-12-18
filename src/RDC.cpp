//
//  RDC.cpp
//  RDC
//
//  Created by Gaston on 11/20/12.
//
//
#include "Camera_A.h"

#include "RDC.h"
RDC::RDC(Camera_A* cam): myCam(cam)
{
    
}

//Public methods
void RDC::calibrate()
{
    vector<float> img = myCam->grabFrame();
    cout << "Camera pixels:" << endl;
    for (int i = 0; i < myCam->getWidth(); i++)
    {
        for (int j = 0; j < myCam->getHeight(); j++)
        {
            cout << img[ Tools::index(i, j, myCam->getWidth()) ] << " ";
        }
        cout << endl;
    }
}

vector<float> RDC::compensate(const vector<float>& srcImg)
{
    vector<float> dstImg;
    
    return dstImg;
}

//Private methods
void RDC::projectStructuredLights()
{

}

void RDC::computeEM()
{
    
}
void RDC::computeFM()
{
}

