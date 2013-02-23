//
//  LSPlane.cpp
//  Laser
//
//  Created by Ou Yuntao on 4/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LSPlane.h"
#include <stdlib.h>
#include <math.h>

LSPlane::LSPlane()
{
    _origin = LSVector(0.0f, 0.0f, 0.0f);
    _norm = LSVector(0.0f, 1.0f, 0.0f);
    _myColor = LSColorFloat_Green;
    _myType = PLANE;
    _reflection = false;
    _refractiveIndex = 1.0f;
    _refraction = false;
    
}

void LSPlane::setPrimitive(float ox, float oy, float oz, float nx, float ny, float nz, LSColorFloat color)
{
    _origin.setX(ox);
    _origin.setY(oy);
    _origin.setZ(oz);
    
    _myColor = color;
    
    _norm.setX(nx);
    _norm.setY(ny);
    _norm.setZ(nz);
    
    _norm.normalise();
}

void LSPlane::setPrimitive(LSVector origin, LSColorFloat color, LSVector norm)
{
    _origin = origin;
    _myColor = color;
    _norm = norm;
    _norm.normalise();
}

LSVector LSPlane::getNorm()
{
    return _norm;
}

void LSPlane::intersect(LSRay &ray, float *t)
{
    ray._direction.normalise();
    _norm.normalise();
    if (t != NULL) {
        if (fabs(ray._direction * _norm) == 0.0f) {
            *t = NAN;
            return;
        }
        *t=((_origin-ray._origin)*_norm)/(ray._direction*_norm);
        if (*t <= ray._zBuffer && (*t >= 0.0f)) {
            ray._zBuffer = *t;
        }else{
            *t=NAN;
        }
    }
}

void LSPlane::intersectNoDepthTest(LSRay &ray, float *t)
{
    ray._direction.normalise();
    _norm.normalise();
    if (t != NULL) {
        if (fabs(ray._direction * _norm) == 0.0f) {
            *t = NAN;
            return;
        }
        *t=((_origin-ray._origin)*_norm)/(ray._direction*_norm);
        if (*t < 0.000001f) {
            *t = NAN;
            return;
        }
    }

}

LSColorFloat LSPlane::getLightColor(LSScene scene, LSRay ray, float t)
{
    return _myColor;
}
