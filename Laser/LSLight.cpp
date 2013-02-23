//
//  LSLight.cpp
//  Laser
//
//  Created by Ou Yuntao on 12-3-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LSLight.h"


LSLight::LSLight()
{
    this->myColor.a=0.0f;
    this->myColor.r=0.0f;
    this->myColor.g=0.0f;
    this->myColor.b=0.0f;
    
    this->myRadius = 0.3f;
    
    this->myPosition=new LSVector;
}

LSLight::LSLight(LSColorFloat color, LSVector* position)
{
    this->myColor = color;
    this->myPosition = position;
    
    this->myRadius = 0.3f;
}

void LSLight::setLight(LSColorFloat color, LSVector* position)
{
    this->myColor = color;
    this->myPosition = position;
}
