//
//  image.h
//  Laser
//
//

#ifndef LSSceneAndRawRender_image_h
#define LSSceneAndRawRender_image_h
#include "LSRaster.h"
void CORasterSaveToPPM(LSRaster* raster, char* path);

void CORasterSaveToBMP(LSRaster* raster, char* path);
#endif
