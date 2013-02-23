//
//  LSVector.h
//  Laser
//
//  Created by Ou Yuntao on 12-1-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef LSSceneAndRawRender_LSVector_h
#define LSSceneAndRawRender_LSVector_h

class LSVector{
public:
    float _x;
    float _y;
    float _z;
public:
    LSVector(float x, float y, float z);
    LSVector(float, float);
    LSVector( void );
    
    void setVec(LSVector vec2);
    void setX(float);
    void setY(float);
    void setZ(float);

    
    float getX() const;
    float getY() const;
    float getZ() const;
    
    void translate(LSVector);
    void translate(float, float, float);
    void scale(float);

    void normalise();
    void normABS();
    float getMagnitude();

    float dotProduct(LSVector);
    
    friend LSVector* crossProduct(LSVector* vec1, LSVector* vec2);
    friend LSVector crossProduct(LSVector vec1, LSVector vec2);
    friend LSVector* vectorSubtract(LSVector* vec1, LSVector* vec2);
    
    float operator*(LSVector);
    LSVector operator*(float scale);
    void operator*=(float scale);
    LSVector operator+(LSVector);
    LSVector operator-(LSVector);
    void operator=(LSVector);
};


#endif
