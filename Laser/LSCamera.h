//
//  LSCamera.h
//  Laser
//
//  Created by Ou Yuntao on 12-2-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef OW3DSceneRender_OWCamera_h
#define OW3DSceneRender_OWCamera_h
#include "LSVector.h"

class LSCamera
{
public:
    LSVector* eyePoint;
    LSVector* lookAtSpot;
    LSVector* upVector;
    LSVector* lookVec;
    LSVector* rightVec;
    
    float fieldOfViewAngleY;
    float aspectRatio;
    
    LSCamera();
    
    void setEyePoint(float ex, float ey, float ez);
    void setLookSpot(float spx, float spy, float spz);
    void setUpVector(float ux, float uy, float uz);
    
    void updateVec();
};


#endif
