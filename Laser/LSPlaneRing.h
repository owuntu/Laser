//
//  LSPlaneRing.h
//  Laser
//
//  Created by Ou Yuntao on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Laser_LSPlaneRing_h
#define Laser_LSPlaneRing_h

#include "LSPlane.h"

class LSPlaneRing : public LSPlane
{
private:
    float _innerRadius;
    float _outerRadius;
public:
    LSPlaneRing();
    LSPlaneRing(float ox, float oy, float oz, 
                float innerRadius, 
                float outerRadius, 
                float nx, float ny, float nz, 
                float red, float green, float blue);
    void setPrimitive(float ox, float oy, float oz, 
                      float innerRadius, 
                      float outerRadius, 
                      float nx, float ny, float nz, 
                      float red, float green, float blue);
    void setPlane(LSVector origin, LSVector normVec);
    void setRadius(float innerRadius, float outerRadius);
    void setInnerRadius(float r);
    void setOuterRadius(float r);
    
    float getInnerRadius();
    float getOuterRadius();
    
    void intersect(LSRay &ray, float *t);
};

#endif
