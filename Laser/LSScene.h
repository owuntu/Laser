//
//  LSScene.h
//  Laser
//
//  Created by Ou Yuntao on 12-2-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef LSSceneAndRawRender_LSScene_h
#define LSSceneAndRawRender_LSScene_h
#include "LSColor.h"
#include "LSLight.h"
#include "LSCamera.h"
#include "LSRaster.h"
#include "LSPrimitive.h"
#include <list>

extern class LSPrimitive;

typedef struct LSScene{
    unsigned rasterWidth;
    unsigned rasterHeight;
    LSRaster raster;
    float minX;
    float minY;
    float maxX;
    float maxY;
    LSCamera camera;
    LSColorFloat ambient;
    std::list<LSLight> lightList;
    int numOfLight;
    std::list<LSPrimitive*>* objectList;
}LSScene;

#endif
