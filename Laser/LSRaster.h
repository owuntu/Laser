//
//  LSRaster.h
//  Laser
//
//  Created by Ou Yuntao on 12-2-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#ifndef LSSceneAndRawRender_LSRaster_h
#define LSSceneAndRawRender_LSRaster_h
#include <stdint.h>

#ifndef LSColorARGB_lib
#define LSColorARGB_lib
typedef uint32_t LSColorARGB;
#endif

#include "LSColor.h"

class LSRaster{
private:
    unsigned width;
    unsigned height;
public:
    LSColorARGB* pixels;
    
    LSRaster(unsigned, unsigned);
    LSRaster();
    
    ~LSRaster();
    
    int getWidth();
    int getHeight();
    
    void setWidth(unsigned w);
    void setHeight(unsigned h);
    void newRaster();
    
    void clear(LSColorFloat);
};


#endif
