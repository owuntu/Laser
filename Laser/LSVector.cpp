//
//  LSVector.cpp
//  Laser
//
//  Created by Ou Yuntao on 12-1-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "LSVector.h"
#include <math.h>

LSVector::LSVector(float x, float y, float z)
{
    _x=x;
    _y=y;
    _z=z;
}

LSVector::LSVector(float x, float y)
{
    _x=x;
    _y=y;
    _z=0.0f;
}

LSVector::LSVector()
{
    _x=_y=_z=0.0f;
}

void LSVector::setVec(LSVector vec2)
{
    _x = vec2.getX();
    _y = vec2.getY();
    _z = vec2.getZ();
}

void LSVector::setX(float x)
{
    this->_x = x;
}
void LSVector::setY(float y)
{
    this->_y = y;
}
void LSVector::setZ(float z)
{
    this->_z = z;
}

float LSVector::getX() const
{
    return this->_x;
}
float LSVector::getY() const
{
    return this->_y;
}
float LSVector::getZ() const
{
    return this->_z;
}

void LSVector::translate(LSVector v)
{
    _x += v.getX();
    _y += v.getY();
    _z += v.getZ();
}
void LSVector::translate(float x, float y, float z)
{
    _x += x;
    _y += y;
    _z += z;
}
void LSVector::scale(float s)
{
    _x *= s;
    _y *= s;
    _z *= s;
}


void LSVector::normalise()
{
    float mag = getMagnitude();
    _x /= mag;
    _y /= mag;
    _z /= mag;
}

void LSVector::normABS()
{
    _x = fabsf(_x);
    _y = fabsf(_y);
    _z = fabsf(_z);
}

float LSVector::getMagnitude()
{
    return sqrt(_x*_x + _y*_y + _z*_z);
}

float LSVector::dotProduct(LSVector v)
{
    return (_x * v.getX() + _y * v.getY() + _z * v.getZ());
}

LSVector* crossProduct(LSVector* vec1, LSVector* vec2)
{
    LSVector* temp = new LSVector;
    temp->setX(vec1->getY()*vec2->getZ() - vec1->getZ()*vec2->getY());
    temp->setY(vec1->getZ()*vec2->getX() - vec1->getX()*vec2->getZ());
    temp->setZ(vec1->getX()*vec2->getY() - vec1->getY()*vec2->getX());
    //temp->setW(1.0f);
    return temp;
}

LSVector crossProduct(LSVector vec1, LSVector vec2)
{
    LSVector* temp = new LSVector;
    temp->setX(vec1.getY() * vec2.getZ() - vec1.getZ() * vec2.getY());
    temp->setY(vec1.getZ() * vec2.getX() - vec1.getX() * vec2.getZ());
    temp->setZ(vec1.getX() * vec2.getY() - vec1.getY() * vec2.getX());
    return *temp;
}

LSVector* vectorSubtract(LSVector* vec1, LSVector* vec2)
{
    LSVector* temp = new LSVector;
    temp->setX(vec1->getX() - vec2->getX());
    temp->setY(vec1->getY() - vec2->getY());
    temp->setZ(vec1->getZ() - vec2->getZ());
    return temp;
}

float LSVector::operator*(LSVector vec2)
{
    return (_x * vec2.getX() + _y * vec2.getY() + _z * vec2.getZ());
}

LSVector LSVector::operator*(float scale)
{
    return LSVector(_x*scale, _y*scale, _z*scale);
}

void LSVector::operator*=(float scale)
{
    _x *= scale;
    _y *= scale;
    _z *= scale;
}

LSVector LSVector::operator+(LSVector vec2)
{
    return LSVector(_x+vec2.getX(), _y+vec2.getY(), _z+vec2.getZ());
}


LSVector LSVector::operator-(LSVector vec2)
{
    return LSVector(_x-vec2.getX(), _y-vec2.getY(), _z-vec2.getZ());
}
void LSVector::operator=(LSVector vec)
{
    _x = vec.getX();
    _y = vec.getY();
    _z = vec.getZ();
}

