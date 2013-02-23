//
//  LSPrimitive.cpp
//  Laser
//
//  Created by Ou Yuntao on 4/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LSPrimitive.h"
#include "LSSphere.h"
#include "LSPlane.h"
#include "LSTriangle.h"
#include "LSPlaneRing.h"
#include <math.h>

PrimitiveType LSPrimitive::getMyType()
{
    return this->_myType;
}

LSColorFloat LSPrimitive::getMyColor()
{
    return  this->_myColor;
}

void LSPrimitive::setPrimitive()
{
    
}

void LSPrimitive::intersect()
{
    
}

LSColorFloat LSPrimitive::getLightColor(LSScene *scene, LSRay ray, float t)
{
    std::list<LSLight>::iterator iterLight;
    std::list<LSPrimitive*>::iterator iterObj;
    LSColorFloat finalColor = LSColorFloat_Dark;
    
    
    std::list<LSPrimitive*>* objList = scene->objectList;
    
    int shadowCount = 0;
    LSVector* intersectPoint = ray.calculateIntersectPoint(t);
    LSVector viewVec = *(scene->camera.eyePoint) - *intersectPoint;
    viewVec.normalise();
    
    LSVector normVec;
    switch (_myType) {
        case SPHERE:
            normVec = ((LSSphere*)this)->calculateNorm(*intersectPoint);
            break;
        case TRIANGLE:
        case PLANE:
        case PLANERING:
            normVec = ((LSPlane*)this)->getNorm();
            break;
        default:
            break;
    }
    normVec.normalise();
    
    float v_dot_n = viewVec * normVec;
    LSColorFloat diffuseSum = LSColorFloat_Dark;
    LSColorFloat reflectColor = LSColorFloat_Dark;
    LSColorFloat refractColor = LSColorFloat_Dark;
    for (iterLight = scene->lightList.begin(); iterLight != scene->lightList.end(); iterLight++) {
        
        LSVector lightVec = *((*iterLight).myPosition) - *intersectPoint;
        lightVec.normalise();
        
        //calculate shadow
        bool shadow = false;
        LSRay rayToLight(*intersectPoint, lightVec);
        for (iterObj = objList->begin(); iterObj != objList->end(); iterObj++) {
            if (this->_reflection == true) {
                break;
            }
            if ((*iterObj) == this) {
                continue;
            }
            float near=NAN;
            float far=NAN;
            switch ((*iterObj)->getMyType()) {
                case SPHERE:
                    ((LSSphere*)(*iterObj))->intersect(rayToLight, &near, &far);
                    break;
                case TRIANGLE:
                    ((LSTriangle*)(*iterObj))->intersect(rayToLight, &near);
                    break;
                case PLANE:
                    ((LSPlane*)(*iterObj))->intersect(rayToLight, &near);
                    break;
                case PLANERING:
                    ((LSPlaneRing*)(*iterObj))->intersect(rayToLight, &near);
                default:
                    break;
            }
            if ((isnan(near) == false || isnan(far) == false)
                && (*iterObj)->_refraction == false
                ) {
                shadow = true;
                //printf("light index=%i\n", (*iterLight).myIndex);
                break;
            }
        }
        
        if (shadow == true) {
            shadowCount++;
            continue;
        }
        
        float l_dot_n = lightVec * normVec;
        float diffContr = fmaxf(l_dot_n, 0.0f);
        //Diffuse lighting;
        LSColorFloat diffuseI = (*iterLight).myColor * _myColor * diffContr;
        diffuseSum = diffuseSum + diffuseI;
        
        
    }
    
    //I am tring to do reflection
    if (_myType == SPHERE && v_dot_n > 0.0f && this->_reflection == true) {
        LSVector reflectVec = normVec*(2.0*v_dot_n) - viewVec;
        LSRay reflectRay(*intersectPoint, reflectVec);
        for (iterObj = objList->begin(); iterObj != objList->end(); iterObj++) {
            if ((*iterObj) == this) {
                continue;
            }
            diffuseSum = LSColorFloat_Dark;
            float near=NAN;
            float far=NAN;
            switch ((*iterObj)->getMyType()) {
                case SPHERE:
                    ((LSSphere*)(*iterObj))->intersect(reflectRay, &near, &far);
                    break;
                case PLANE:
                    ((LSPlane*)(*iterObj))->intersect(reflectRay, &near);
                    break;
                case TRIANGLE:
                    ((LSTriangle*)(*iterObj))->intersect(reflectRay, &near);
                    break;
                    
                default:
                    break;
            }
            if (isnan(near) == false) {
                LSColorFloat tempColor = (*iterObj)->getLightColor(scene, reflectRay, near);
                reflectColor = tempColor;
            }
        }
    }
    
    //refraction
    //for sphere refraction
    if (_myType == SPHERE && v_dot_n > 0.0f && this->_refraction == true) {
        //entrance ray
        LSRay* refracRay1 = NULL;
        refracRay1 = ((LSSphere*)this)->calculateRefractiveRay(ray, t);
        /****test******
        float refrK = 1.0f/this->_refractiveIndex;
        float cosTview = v_dot_n;
        float sinTrfrSq = refrK * refrK * (1.0 - cosTview*cosTview);
        LSVector normNeg;
        LSVector refraVec = viewVec * (-1.0 * refrK) + normVec * (refrK*cosTview + sqrtf(1.0f - sinTrfrSq) * (1.0f));
        refraVec.normalise();
        //refracRay1 = &ray;
        refracRay1->_direction = refraVec;
        refracRay1->_origin = *intersectPoint;
        float distance = (refracRay1->_origin - ((LSSphere*)this)->_origin).getMagnitude();
         /************/
        diffuseSum = LSColorFloat_Dark;
        float tempNear = NAN;
        float tempFar = NAN;
        if (refracRay1 != NULL) {
            ((LSSphere*)this)->intersect(*refracRay1, &tempNear, &tempFar);
            refracRay1->_zBuffer = 0xFFFFFFFF;
            //exit ray
            LSRay* refracRay2 = NULL;
            if (isnan(tempNear)==false || isnan(tempFar) == false) {
                if (isnan(tempNear) == false) {
                    refracRay2 = ((LSSphere*)this)->calculateRefractiveRay(*refracRay1, tempNear);
                }else if(isnan(tempFar) == false){
                    refracRay2 = ((LSSphere*)this)->calculateRefractiveRay(*refracRay1, tempFar);
                }
                LSRay* tempRay = refracRay1;
                if (tempRay != NULL) {
                    for (iterObj = objList->begin(); iterObj != objList->end(); iterObj++) {
                        if ((*iterObj) == this) {
                            continue;
                        }
                        float near2=NAN;
                        float far2=NAN;
                        switch ((*iterObj)->getMyType()) {
                            case SPHERE:
                                ((LSSphere*)(*iterObj))->intersect(*tempRay, &near2, &far2);
                                break;
                            case PLANE:
                                ((LSPlane*)(*iterObj))->intersect(*tempRay, &near2);
                                break;
                            case TRIANGLE:
                                ((LSTriangle*)(*iterObj))->intersect(*tempRay, &near2);
                                break;
                                
                            default:
                                break;
                        }
                        if (isnan(near2) == false) {
                            LSColorFloat tempColor = (*iterObj)->getLightColor(scene, *tempRay, near2);
                            refractColor = tempColor;
                            continue;
                        }
                    }
                }
            }
        }
    }
    
    LSColorFloat ambientI = _myColor * (scene->ambient);
    if (this->_reflection == true || this->_refraction == true) {
        ambientI = LSColorFloat_Dark;
    }
    finalColor = diffuseSum + ambientI + reflectColor + refractColor;
    colorNormalise(finalColor);
    
    return finalColor;
}

LSVector LSPrimitive::calculateNorm()
{
    LSVector tempVec(0.0f, 1.0f, 0.0f);
    return tempVec;
}

LSRay* LSPrimitive::calculateRefractiveRay(LSRay inRay, float t)
{
    LSRay* temp = &inRay;
    return temp;
}

void LSPrimitive::setMyColor(LSColorFloat color)
{
    _myColor = color;
}