//
//  LSPlane.h
//  Laser
//
//  Created by Ou Yuntao on 4/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Laser_LSPlane_h
#define Laser_LSPlane_h

#include "LSPrimitive.h"
#include "LSVector.h"
#include "LSRay.h"
#include "LSScene.h"
#include "LSColor.h"

class LSPlane : public LSPrimitive
{
public:
    LSVector _origin;
    LSVector _norm;
    
public:
    LSPlane();
    
    void setPrimitive(float ox, float oy, float oz, float nx, float ny, float nz, LSColorFloat color);
    void setPrimitive(LSVector origin, LSColorFloat color, LSVector norm);
    
    LSVector getNorm();
    
    void intersect(LSRay &ray, float *t);
    void intersectNoDepthTest(LSRay &ray, float *t);

    LSColorFloat getLightColor(LSScene scene, LSRay ray, float t);
    
};

#endif
