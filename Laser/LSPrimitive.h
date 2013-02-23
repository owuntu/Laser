//
//  LSPrimitive.h
//  Laser
//
//  Created by Ou Yuntao on 4/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Laser_Primitive_h
#define Laser_Primitive_h
#include "LSColor.h"
#include "LSVector.h"
#include "LSRay.h"
#include "LSScene.h"

//extern class LSSphere;
//extern class LSPlane;

class LSScene;

enum PrimitiveType {SPHERE, PLANE, TRIANGLE, PLANERING};

class LSPrimitive{
public:
    bool _reflection;
    bool _refraction;
    float _refractiveIndex;
    virtual void setPrimitive();
    virtual void intersect();
    //virtual void setPrimitive(float x, float y, float z, float radius, LSColorChannelFloat r, LSColorChannelFloat g, LSColorChannelFloat b);
    PrimitiveType getMyType();
    LSColorFloat getMyColor();
    virtual LSColorFloat getLightColor(LSScene *scene, LSRay ray, float t);
    virtual LSVector calculateNorm();
    
    virtual LSRay* calculateRefractiveRay(LSRay inRay, float t);
    
    void setMyColor(LSColorFloat color);
protected:
    PrimitiveType _myType;
    LSColorFloat _myColor;
};

#endif
