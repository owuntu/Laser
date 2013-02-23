//
//  LSTriangle.cpp
//  Laser
//
//  Created by Ou Yuntao on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LSTriangle.h"
#include <math.h>
LSTriangle::LSTriangle()
{
    _myType = TRIANGLE;
    
    _maxX = 1000.f;
    _maxY = 1000.f;
    _maxZ = 1000.f;
    
    _minX = -1000.f;
    _minY = -1000.f;
    _minZ = -1000.f;
}

void LSTriangle::setPrimitive(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, LSColorChannelFloat r, LSColorChannelFloat g, LSColorChannelFloat b)
{
    vec[0].setVec(LSVector(x1, y1, z1)); 
    vec[1].setVec(LSVector(x2, y2, z2));
    vec[2].setVec(LSVector(x3, y3, z3));
    
    _maxX = fmaxf(x1, fmaxf(x2, x3));
    _maxY = fmaxf(y1, fmaxf(y2, y3));
    _maxZ = fmaxf(z1, fmaxf(z2, z3));
    
    _minX = fminf(x1, fminf(x2, x3));
    _minY = fminf(y1, fminf(y2, y3));
    _minZ = fminf(z1, fminf(z2, z3));
    
    _origin = vec[0];
    _myColor = LSColorFloatMake(1.0f, r, g, b);
    _norm = crossProduct(vec[1]-vec[0], vec[2]-vec[0]);
    _norm.normalise();
    
    b_a = vectorSubtract(&(this->vec[1]), &(this->vec[0]));
    c_b = vectorSubtract(&(this->vec[2]), &(this->vec[1]));
    a_c = vectorSubtract(&(this->vec[0]), &(this->vec[2]));
    
    tempVec2 = crossProduct(b_a, c_b);
}

void LSTriangle::intersect(LSRay &ray, float *t)
{
    //ray._direction.normalise();
    //_norm.normalise();
    //_norm.normABS();
    if (t != NULL) {
        if (fabs(ray._direction * _norm) < 0.000001f) {
            *t = NAN;
            return;
        }
        *t=((_origin-ray._origin)*_norm)/(ray._direction*_norm);
        /****************TO SOLVE: zBuffer****************/
        if (*t < 0.00001f) {
            *t=NAN;
            return;
        }
    }
    //this->LSPlane::intersect(ray, t);
    
    LSVector* intersectPoint = ray.calculateIntersectPoint(*t);
    
    if (intersectPoint->getX() > _maxX || intersectPoint->getY() > _maxY 
        //|| intersectPoint->getZ() > _maxZ
        || intersectPoint->getX() < _minX || intersectPoint->getY() < _minY 
        //|| intersectPoint->getZ() < minZ
        ) {
        *t = NAN;
        return;
    }
    
    float lam0=1.0f;
    float lam1=1.0f;
    float lam2=1.0f;

    LSVector* tempVec1;

    float tempMag;
    
    LSVector* b_p = vectorSubtract(&(this->vec[1]), (intersectPoint));
    LSVector* c_p = vectorSubtract(&(this->vec[2]), (intersectPoint));
    LSVector* a_p = vectorSubtract(&(this->vec[0]), (intersectPoint));
    
    //float mag2 = tempVec2->getMagnitude();
    
    tempVec1 = crossProduct(b_p, c_b);
    //lam0 = tempVec1->getMagnitude() / mag2;
    tempMag = *tempVec1 * *tempVec2;
    lam0 = tempMag / fabsf(tempMag);
    delete tempVec1;
    
    tempVec1 = crossProduct(c_p, a_c);
    //lam1 = tempVec1->getMagnitude() / mag2;
    tempMag = *tempVec1 * *tempVec2;
    lam1 = tempMag / fabsf(tempMag);
    delete tempVec1;
    
    tempVec1 = crossProduct(a_p, b_a);
    //lam2 = tempVec1->getMagnitude() / mag2;
    tempMag = *tempVec1 * *tempVec2;
    lam2 = tempMag / fabsf(tempMag);
    delete tempVec1;
    
    if (!(lam0 > 0 && lam1 > 0 && lam2 > 0) || *t>ray._zBuffer) {
        *t=NAN;
    }else{
        ray._zBuffer = *t;
    }
    
    /******
    if (_myIndex == 2) {
        //printf("P in cal:%f, %f, %f\n", intersectPoint.getX(), intersectPoint.getY(), intersectPoint.getZ());
        //printf("raydir:%f, %f, %f\n", ray._direction.getX(), ray._direction.getY(), ray._direction.getZ());
    }
    if (_myIndex==2 && isnan(*t) == false) {
        //printf("t=%f\n",*t);
    }
     ******/
}

void LSTriangle::printInfo()
{
    printf("Triangle[%i]\nColor = %f, %f, %f\n", _myIndex, _myColor.r, _myColor.g, _myColor.b);
    printf("coord:%f, %f, %f, %f, %f, %f, %f, %f, %f\n", vec[0].getX(), vec[0].getY(), vec[0].getZ(), 
                                                       vec[1].getX(), vec[1].getY(), vec[1].getZ(), 
                                                       vec[2].getX(), vec[2].getZ(), vec[2].getZ());
}
