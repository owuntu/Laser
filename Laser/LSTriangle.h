//
//  LSTriangle.h
//  Laser
//
//  Created by Ou Yuntao on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Laser_LSTriangle_h
#define Laser_LSTriangle_h

#include "LSPlane.h"
#include "LSColor.h"

class LSTriangle : public LSPlane
{
public:
    LSVector vec[3];
    int _myIndex;
private:
    float _maxX;
    float _maxY;
    float _maxZ;
    
    float _minX;
    float _minY;
    float _minZ;
    
    LSVector* b_a;
    LSVector* c_b;
    LSVector* a_c;
    
    LSVector* tempVec2;
public:
    LSTriangle();
    void setPrimitive(float x1, float y1, float z1, 
                      float x2, float y2, float z2, 
                      float x3, float y3, float z3, 
                      LSColorChannelFloat r, LSColorChannelFloat g, LSColorChannelFloat b);

    void intersect(LSRay &ray, float *t);
    void printInfo();
};
#endif
