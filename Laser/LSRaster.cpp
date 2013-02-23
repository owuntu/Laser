//
//  LSRaster.cpp
//  Laser
//
//  Created by Ou Yuntao on 12-2-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "LSRaster.h"
#include <stdlib.h>
LSRaster::LSRaster(unsigned w, unsigned h)
{
    this->width = w;
    this->height = h;
    pixels = new LSColorARGB[width*height];
}
LSRaster::LSRaster()
{
    width = height = 1;
    pixels = new LSColorARGB[width*height];
}
LSRaster::~LSRaster()
{
    delete pixels;
    pixels = NULL;
}

int LSRaster::getWidth()
{
    return (int)width;
}

int LSRaster::getHeight()
{
    return (int)height;
}

void LSRaster::setWidth(unsigned w)
{
    this->width = w;
}

void LSRaster::setHeight(unsigned h)
{
    this->height = h;
}

void LSRaster::newRaster()
{
    delete pixels;
    pixels = new LSColorARGB[width*height];
}

void LSRaster::clear(LSColorFloat color)
{
    int numOfPixels = (int)(width * height);
    for (int i=0; i<numOfPixels; i++) {
        pixels[i] = drawARGBColorFromFloatColor(color);
    }
}
