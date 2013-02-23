//
//  LSRay.h
//  Laser
//
//  Created by Ou Yuntao on 4/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Laser_LSRay_h
#define Laser_LSRay_h

#include "LSVector.h"
#include "LSColor.h"

class LSRay{
public:
    LSVector _origin;
    LSVector _direction;
    float _zBuffer;
    float _curRfrIndex; // current material refractive index
public:
    int _numOfreflect;
public:
    LSRay();
    LSRay(LSVector o, LSVector dir);
    
    LSVector* calculateIntersectPoint(float t);
};

#endif
