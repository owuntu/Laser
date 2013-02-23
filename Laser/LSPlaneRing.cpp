//
//  LSPlaneRing.cpp
//  Laser
//
//  Created by Ou Yuntao on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LSPlaneRing.h"
#include <math.h>

LSPlaneRing::LSPlaneRing()
{
    _innerRadius = 1.0f;
    _outerRadius = 2.0f;
    _myType = PLANERING;
}

LSPlaneRing::LSPlaneRing(float ox, float oy, float oz, 
            float innerRadius, 
            float outerRadius, 
            float nx, float ny, float nz, 
            float red, float green, float blue)
{
    this->_origin.setX(ox);
    this->_origin.setY(oy);
    this->_origin.setZ(oz);
    
    _innerRadius = innerRadius;
    _outerRadius = outerRadius;
    
    this->_norm.setX(nx);
    this->_norm.setY(ny);
    this->_norm.setZ(nz);
    
    _myColor = LSColorFloatMake(1.0f, red, green, blue);
    
    _myType = PLANERING;
}

void LSPlaneRing::setPrimitive(float ox, float oy, float oz, 
                               float innerRadius, 
                               float outerRadius, 
                               float nx, float ny, float nz, 
                               float red, float green, float blue)
{
    this->_origin.setX(ox);
    this->_origin.setY(oy);
    this->_origin.setZ(oz);
    
    _innerRadius = innerRadius;
    _outerRadius = outerRadius;
    
    this->_norm.setX(nx);
    this->_norm.setY(ny);
    this->_norm.setZ(nz);
    
    _myColor = LSColorFloatMake(1.0f, red, green, blue);
}

void LSPlaneRing::setPlane(LSVector origin, LSVector normVec)
{
    this->_origin = origin;
    this->_norm = normVec;
}

void LSPlaneRing::setRadius(float innerRadius, float outerRadius)
{
    this->_innerRadius = innerRadius;
    this->_outerRadius = outerRadius;
}

void LSPlaneRing::setInnerRadius(float r)
{
    this->_innerRadius = r;
}

void LSPlaneRing::setOuterRadius(float r)
{
    this->_outerRadius = r;
}

float LSPlaneRing::getInnerRadius()
{
    return this->_innerRadius;
}

float LSPlaneRing::getOuterRadius()
{
    return this->_outerRadius;
}


void LSPlaneRing::intersect(LSRay &ray, float *t)
{
    ((LSPlane*)this)->intersectNoDepthTest(ray, t);
    if (isnan(*t)) {
        return;
    }
    LSVector *intersectPoint = ray.calculateIntersectPoint(*t);
    float tempD = (*intersectPoint - _origin).getMagnitude();
    if (tempD < _innerRadius || tempD > _outerRadius) {
        if (t!=NULL)
            *t = NAN;
        return;
    }
    if (*t <= ray._zBuffer) {
        ray._zBuffer = *t;
    }else{
        *t=NAN;
        return;
    }
}
