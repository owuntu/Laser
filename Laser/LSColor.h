//
//  LSColor.h
//  Laser
//
//  Created by Ou Yuntao on 12-2-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef LSSceneAndRawRender_LSColor_h
#define LSSceneAndRawRender_LSColor_h

#include <stdint.h>

#ifndef LSColorChannelFloat_lib
#define LSColorChannelFloat_lib
typedef float LSColorChannelFloat;
#endif

#ifndef LSColorARGB_lib
#define LSColorARGB_lib
typedef uint32_t LSColorARGB;
#endif

#ifndef LSColorChannelByte_lib
#define LSColorChannelByte_lib
typedef uint8_t LSColorChannelByte;
#endif

#ifndef LSColorFloat_lib
#define LSColorFloat_lib
struct LSColorFloat{
    LSColorChannelFloat a;
    LSColorChannelFloat r;
    LSColorChannelFloat g;
    LSColorChannelFloat b;
};
typedef struct LSColorFloat LSColorFloat;
#endif

LSColorFloat LSColorFloatMake(LSColorChannelFloat a, LSColorChannelFloat r, LSColorChannelFloat g, LSColorChannelFloat b);
void colorNormalise(LSColorFloat& color);
LSColorFloat colorAdd(LSColorFloat color1, LSColorFloat color2);
void colorScale(LSColorFloat& color, float s);

LSColorFloat operator+(LSColorFloat color1, LSColorFloat color2);
LSColorFloat operator*(LSColorFloat color1, LSColorFloat color2);
LSColorFloat operator*(LSColorFloat color, float s);
void operator*=(LSColorFloat &color, float s);

LSColorARGB drawARGBColorFromFloatColor(LSColorChannelFloat, LSColorChannelFloat, LSColorChannelFloat);
LSColorARGB drawARGBColorFromFloatColor(LSColorFloat);

#define LSColorFloat_Dark LSColorFloatMake(1.0f, 0.0f, 0.0f, 0.0f)
#define LSColorFloat_Red LSColorFloatMake(1.0f, 1.0f, 0.0f, 0.0f)
#define LSColorFloat_Green LSColorFloatMake(1.0f, 0.0f, 1.0f, 0.0f)
#define LSColorFloat_Blue LSColorFloatMake(1.0f, 0.0f, 0.0f, 1.0f)
#define LSColorFloat_Dark LSColorFloatMake(1.0f, 0.0f, 0.0f, 0.0f)
#define LSColorFloat_White LSColorFloatMake(1.0f, 1.0f, 1.0f, 1.0f)

#endif
