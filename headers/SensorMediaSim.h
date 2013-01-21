//
//  SensorMediaSim.h
//  RDC
//
//  Created by Gaston on 12/21/12.
//
//

#ifndef RDC_SensorMediaSim_h
#define RDC_SensorMediaSim_h

#include "common.h"
#include "Sensor_A.h"

class SensorMediaSim : public Sensor_A{
public:
    SensorMediaSim(int w, int h);
    virtual void init();
    virtual Image grabFrame();
    
private:
    
};

#endif
