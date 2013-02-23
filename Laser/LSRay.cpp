//
//  File.cpp
//  Laser
//
//  Created by Ou Yuntao on 4/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LSRay.h"

LSRay::LSRay()
{
    _origin = LSVector(0.0f, 0.0f, 0.0f);
    _direction = LSVector(0.0f, 0.0f, 1.0f);
    _zBuffer = 10000.f;
    _curRfrIndex = 1.0f;
}

LSRay::LSRay(LSVector o, LSVector dir)
{
    _origin = o;
    _direction = dir;
    _direction.normalise();
    _zBuffer = 0xFFFFFFFF;
    _curRfrIndex = 1.0f;
}

LSVector* LSRay::calculateIntersectPoint(float t)
{
    //_direction.normalise();
    LSVector intersectPoint = _origin + _direction * t;
    LSVector* temp = new LSVector(intersectPoint);
    return temp;
}