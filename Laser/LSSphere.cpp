//
//  LSSphere.cpp
//  Laser
//
//  Created by Ou Yuntao on 4/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LSSphere.h"
#include "LSVector.h"
#include <math.h>

LSSphere::LSSphere()
{
    _origin = LSVector(0.0f, 0.0f, 0.0f);
    _radius = 0.0f;
    _myColor = LSColorFloat_Dark;
    _myType = SPHERE;
    _reflection = false;
    _refractiveIndex = 1.0f;
    _refraction = false;
    
    rayHitC = inErrC = outErrC = 0;
}

LSSphere::LSSphere(LSVector origin, float radius, LSColorFloat color)
{
    this->_origin = origin;
    this->_radius = radius;
    _myColor = color;
    _myType = SPHERE;
    _reflection = false;
    _refractiveIndex = 1.0f;
    _refraction = false;
    
    rayHitC = inErrC = outErrC = 0;
}

void LSSphere::intersect(LSRay& ray, float* nearIntersect, float* farIntersect)
{
    ray._direction.normalise();
    float a = ray._direction * ray._direction;
    float b = 2 * (ray._direction * (ray._origin - this->_origin));
    float c = (ray._origin - this->_origin) * (ray._origin - this->_origin) - this->_radius * this->_radius;
    float h = b*b-4*a*c;
    
    if(h<0){//the ray miss the sphere
        if (nearIntersect != NULL) {
            *nearIntersect = NAN;
        }
        if (farIntersect !=NULL) {
            *farIntersect = NAN;
        }
        return;
    }else if (h==0) {
        *nearIntersect = *farIntersect = -1.0f * b / (2.0f * a);
    }else{
        float sqrH = sqrtf(h);
        float rootMin = (-1.0f * b - sqrH) / (2.0f * a);
        float rootMax = (-1.0f * b + sqrH) / (2.0f * a);
        if (rootMax < rootMin) {
            float t = rootMax;
            rootMax = rootMin;
            rootMin = t;
        }
        if (rootMin<0.00f) {
            if (rootMax> -0.00f) {
                *nearIntersect = rootMax;
                if (farIntersect != NULL) {
                    *farIntersect = NAN;
                }
            }else{ // The sphere on the back side of the ray
                if (nearIntersect != NULL) {
                    *nearIntersect = NAN;
                }
                if (farIntersect !=NULL) {
                    *farIntersect = NAN;
                }
                return;
            }
        }else{
            *nearIntersect = rootMin;
            *farIntersect = rootMax;
        }
    }
    
    if (*nearIntersect>ray._zBuffer) {
        *nearIntersect = NAN;
    }else{
        ray._zBuffer = *nearIntersect;
    }
}

/*
LSColorFloat LSSphere::getLightColor(LSScene *scene, LSRay ray, float t)
{
    std::list<LSLight>::iterator iterLight;
    LSColorFloat finalColor = LSColorFloat_Dark;
    for (iterLight = scene->lightList.begin(); iterLight != scene->lightList.end(); iterLight++) {
        LSVector intersectPoint = ray.calculateIntersectPoint(t);
        LSVector normVec = calculateNorm(intersectPoint);
        normVec.normalise();
        
        LSVector lightVec = *((*iterLight).myPosition) - intersectPoint;
        lightVec.normalise();
        
        LSVector viewVec = *(scene->camera.eyePoint) - intersectPoint;
        viewVec.normalise();
        
        float l_dot_n = lightVec * normVec;
        float diffContr = fmaxf(l_dot_n, 0.0f);
        
        LSColorFloat diffuseI = (*iterLight).myColor * _myColor * diffContr;
        finalColor = finalColor + diffuseI;
    }
    colorNormalise(finalColor);
    return finalColor;
}
*/

LSVector LSSphere::calculateNorm(LSVector pointOnSurface)
{
    LSVector norm = pointOnSurface - _origin;
    norm.normalise();
    return norm;
}


void LSSphere::setPrimitive(float x, float y, float z, float radius, LSColorChannelFloat r, LSColorChannelFloat g, LSColorChannelFloat b)
{
    _origin.setX(x);
    _origin.setY(y);
    _origin.setZ(z);
    _radius = radius;
    _myColor.r = r;
    _myColor.g = g;
    _myColor.b = b;
}

void LSSphere::setPrimitive(LSVector origin)
{
    _origin = origin;
}

void LSSphere::setPrimitive(float radius)
{
    _radius = radius;
}

void LSSphere::setPrimitive(LSColorFloat color)
{
    _myColor = color;
}

LSRay* LSSphere::calculateRefractiveRay(LSRay inRay, float t)
{
    rayHitC++;
    LSVector* interPoint = inRay.calculateIntersectPoint(t);
    float refractiveK;
    float rayOtoSphereO = (inRay._origin - _origin).getMagnitude();
    LSVector normVec = this->calculateNorm(*interPoint);
    if (rayOtoSphereO <= this->_radius + 0.0f) {
        //ray inside the sphere
        refractiveK = inRay._curRfrIndex;
        normVec = normVec*(-1);
        if (refractiveK < 1.1f && refractiveK > 0.9f) {
            printf("inside refractiveK warning[%i]: %f\n", inErrC, refractiveK);
            inErrC++;
        }
    }else{
        refractiveK = inRay._curRfrIndex / _refractiveIndex;
        if (refractiveK < 1.1f && refractiveK > 0.9f) {
            printf("outside refractiveK warning[%i]: %f\n", outErrC, refractiveK);
            outErrC++;
        }
    }
    
    /********use translucent to test************/
    //refractiveK = 1.0;

    LSVector viewVec = inRay._direction * (-1.0f);
    viewVec.normalise();
    float cosTview = inRay._direction * normVec;
    float sinTrfrSq = refractiveK * refractiveK * (1 - cosTview*cosTview);
    
    if (sinTrfrSq > 1.0f) {
        return NULL;
        sinTrfrSq = 1.0f;
        cosTview = 0.0f;
    }
    
    LSVector refracVec;
    refracVec = inRay._direction * (refractiveK) - normVec * (refractiveK * cosTview + sqrtf(1.0f - sinTrfrSq));
    //refracVec = viewVec * (-1.0f) + normVec * (-1.0f);
    //refracVec = refracVec * (-1.0f);
    refracVec.normalise();
    LSRay* refracRay = new LSRay(*interPoint, refracVec);
    if (refractiveK < 1.0f) {
        refracRay->_curRfrIndex = _refractiveIndex;
    }
    
    //refracRay = &inRay;
    refracRay->_zBuffer = 0xFFFFFFFF;
    return refracRay;
}