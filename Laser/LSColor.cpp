//
//  LSColor.cpp
//  Laser
//
//  Created by Ou Yuntao on 12-2-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "LSColor.h"
#include <math.h>
LSColorFloat LSColorFloatMake(LSColorChannelFloat a, LSColorChannelFloat r, LSColorChannelFloat g, LSColorChannelFloat b)
{
    LSColorFloat tempColor;
    tempColor.a = a;
    tempColor.r = r;
    tempColor.g = g;
    tempColor.b = b;
    
    return tempColor;
}

void colorNormalise(LSColorFloat& color)
{
    if (color.a > 1.0f)
        color.a = 1.0f;
    
    float maxChannel = fmaxf(color.r, fmaxf(color.g, color.b));
    if (maxChannel > 1.0f) {
        color.r /= maxChannel;
        color.g /= maxChannel;
        color.b /= maxChannel;
    }
}
LSColorFloat colorAdd(LSColorFloat color1, LSColorFloat color2)
{
    LSColorFloat tempColor;
    tempColor.a = color1.a + color2.a;
    tempColor.r = color1.r + color2.r;
    tempColor.g = color1.g + color2.g;
    tempColor.b = color1.b + color2.b;
    return tempColor;
}

void colorScale(LSColorFloat& color, float s)
{
    color.a *= s;
    color.r *= s;
    color.g *= s;
    color.b *= s;
}

LSColorFloat operator+(LSColorFloat color1, LSColorFloat color2)
{
    LSColorFloat tempColor;
    tempColor.a = color1.a + color2.a;
    tempColor.r = color1.r + color2.r;
    tempColor.g = color1.g + color2.g;
    tempColor.b = color1.b + color2.b;
    return tempColor;
}

LSColorFloat operator*(LSColorFloat color1, LSColorFloat color2)
{
    LSColorFloat tempColor;
    tempColor.a = color1.a * color2.a;
    tempColor.r = color1.r * color2.r;
    tempColor.g = color1.g * color2.g;
    tempColor.b = color1.b * color2.b;
    return tempColor;
}

LSColorFloat operator*(LSColorFloat color, float s)
{
    LSColorFloat tempColor;
    tempColor.a = color.a * s;
    tempColor.r = color.r * s;
    tempColor.g = color.g * s;
    tempColor.b = color.b * s;
    return tempColor;
}

void operator*=(LSColorFloat &color, float s)
{
    color.a *= s;
    color.r *= s;
    color.g *= s;
    color.b *= s;
}

LSColorARGB drawARGBColorFromFloatColor(LSColorChannelFloat red, LSColorChannelFloat green, LSColorChannelFloat blue)
{
    LSColorARGB argbColor = 0x00000000;
    LSColorChannelByte a = (LSColorChannelByte)255;
    LSColorChannelByte r = (LSColorChannelByte)(red * 255.f);
    LSColorChannelByte g = (LSColorChannelByte)(green * 255.f);
    LSColorChannelByte b = (LSColorChannelByte)(blue * 255.f);
    
    argbColor = argbColor | (((LSColorARGB)a) << 24);
    argbColor = argbColor | (((LSColorARGB)r) << 16);
    argbColor = argbColor | (((LSColorARGB)g) << 8);
    argbColor = argbColor | (((LSColorARGB)b) << 0);
    
    return argbColor;
}

LSColorARGB drawARGBColorFromFloatColor(LSColorFloat color)
{
    LSColorARGB argbColor = 0x00000000;
    LSColorChannelByte a = (LSColorChannelByte)255;
    LSColorChannelByte r = (LSColorChannelByte)(color.r * 255.f);
    LSColorChannelByte g = (LSColorChannelByte)(color.g * 255.f);
    LSColorChannelByte b = (LSColorChannelByte)(color.b * 255.f);
    
    argbColor = argbColor | (((LSColorARGB)a) << 24);
    argbColor = argbColor | (((LSColorARGB)r) << 16);
    argbColor = argbColor | (((LSColorARGB)g) << 8);
    argbColor = argbColor | (((LSColorARGB)b) << 0);
    
    return argbColor;
}