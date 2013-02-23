//
//  LSSphere.h
//  Laser
//
//  Created by Ou Yuntao on 4/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Laser_LSSphere_h
#define Laser_LSSphere_h

#include "LSVector.h"
#include "LSColor.h"
#include "LSRay.h"
#include "LSPrimitive.h"
#include "LSLight.h"
#include "LSScene.h"
#include <list.h>

class LSSphere : public LSPrimitive
{
public:
    LSVector _origin;
    float _radius;
    
    int inErrC;
    int outErrC;
    int rayHitC;
public:
    LSSphere();
    LSSphere(LSVector origin, float radius, LSColorFloat color);
    
    void intersect(LSRay& ray, float* nearIntersect, float* farIntersect);
    
    void setPrimitive(float x, float y, float z, float radius, LSColorChannelFloat r, LSColorChannelFloat g, LSColorChannelFloat b);
    void setPrimitive(LSVector origin);
    void setPrimitive(float radius);
    void setPrimitive(LSColorFloat color);
    
    //LSColorFloat getLightColor(LSScene *scene, LSRay ray, float t);
    LSVector calculateNorm(LSVector pointOnSurface);
    LSRay* calculateRefractiveRay(LSRay inRay, float t);
};

#endif
