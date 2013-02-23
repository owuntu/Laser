//
//  LSLight.h
//  Laser
//
//  Created by Ou Yuntao on 12-3-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef OW3DSceneRender_LSLight_h
#define OW3DSceneRender_LSLight_h
#include "LSColor.h"
#include "LSVector.h"
class LSLight
{
public:
    LSColorFloat myColor;
    LSVector* myPosition;
    float myRadius;
    int myIndex;
public:
    LSLight();
    LSLight(LSColorFloat color, LSVector* position);
    
    void setLight(LSColorFloat color, LSVector* position);
};

#endif
