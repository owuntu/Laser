//
//  LSCamera.cpp
//  Laser
//
//  Created by Ou Yuntao on 12-2-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "LSCamera.h"

LSCamera::LSCamera()
{
    this->eyePoint=new LSVector;
    this->lookAtSpot = new LSVector;
    this->upVector = new LSVector;
    this->lookVec = new LSVector;
    this->rightVec = new LSVector;
    
}

void LSCamera::setEyePoint(float ex, float ey, float ez)
{
    eyePoint->setX(ex);
    eyePoint->setY(ey);
    eyePoint->setZ(ez);
}
void LSCamera::setLookSpot(float spx, float spy, float spz)
{
    lookAtSpot->setX(spx);
    lookAtSpot->setY(spy);
    lookAtSpot->setZ(spz);
}
void LSCamera::setUpVector(float ux, float uy, float uz)
{
    upVector->setX(ux);
    upVector->setY(uy);
    upVector->setZ(uz);
}

void LSCamera::updateVec()
{
    delete lookVec;
    lookVec = vectorSubtract(lookAtSpot,eyePoint);
    lookVec->normalise();
    
    delete rightVec;
    rightVec = crossProduct(lookVec, upVector);
    rightVec->normalise();
    
    delete upVector;
    upVector = crossProduct(rightVec, lookVec);
    upVector->normalise();
}