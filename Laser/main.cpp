//
//  main.cpp
//  Laser
//
//  Created by Ou Yuntao on 4/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//==============================I am the fantastic seperated line==========================//
//======================================END================================================//


#include "image.h"
#include "LSVector.h"
#include "LSRaster.h"
#include "LSColor.h"
#include "LSRaster.h"
#include "LSSphere.h"
#include "LSPlane.h"
#include "LSTriangle.h"
#include "LSPlaneRing.h"
#include "LSSceneFileReader.h"
#include <math.h>
#include <time.h>

int main (int argc, const char * argv[])
{
    time_t start, end;
    double timeCost = 0.0;
    time(&start);
    
    //Scene file reader
    FILE* sceneFile = fopen("scene.urt", "r");
    if (sceneFile == NULL) {
        printf("Error. Could not open scene file.\n");
        return 1;
    }
    LSScene scene;
    scene.objectList = new list<LSPrimitive*>;
    std::list<LSPrimitive*>* primList = scene.objectList;
    sceneFileReader(sceneFile, scene);
    scene.camera.updateVec();
    
    LSVector eye = *(scene.camera.eyePoint);
    //(scene.camera.lookVec)->normalise();
    LSVector screenCenter = eye + *(scene.camera.lookVec);
        //+ (*(scene.camera.lookVec) * ((scene.camera.lookVec)->getMagnitude()/tanf(scene.camera.fieldOfViewAngleY/2.0f)));
    float screenVMagnitude = tanf(scene.camera.fieldOfViewAngleY/2.0f);
    float screenUMagnitude = screenVMagnitude * scene.camera.aspectRatio;
    
    LSVector screenU = *(scene.camera.rightVec) * screenUMagnitude;
    LSVector screenV =  *(scene.camera.upVector) * screenVMagnitude;
    int rasterWidth = scene.raster.getWidth();
    int rasterHeight = scene.raster.getHeight();
    
    //add refraction on the third object
    std::list<LSPrimitive*>::iterator iterObj;
    iterObj = scene.objectList->begin();
    iterObj++;
    iterObj++;
    (*iterObj)->_refraction = true;
    (*iterObj)->_refractiveIndex = 1.8f;
    //(*iterObj)->setMyColor(LSColorFloat_White);
    /***/
    
    LSVector sC_eye = screenCenter - eye;
    LSVector rayOrigin = eye;
    LSVector u;
    LSVector v;
    
    for (int x = 0; x<rasterWidth; x++) {
        for (int y=0; y<rasterHeight; y++) {
            u = screenU * ((float)x / (float)rasterWidth * 2.0f - 1.0f);
            v = screenV * ((float)y / (float)rasterHeight * 2.0f - 1.0f);
            
            LSVector rayDirection = sC_eye + u + v;
            
            LSRay ray(rayOrigin, rayDirection);
            float near = NAN;
            float far = NAN;
            for (list<LSPrimitive*>::iterator iterPr=primList->begin(); iterPr != primList->end(); iterPr++) {
                
                switch ((*iterPr)->getMyType()) {
                    case SPHERE:
                        ((LSSphere*)(*iterPr))->intersect(ray, &near, &far);
                        break;
                    case PLANE:
                        ((LSPlane*)(*iterPr))->intersect(ray, &near);
                        break;
                    case TRIANGLE:
                        ((LSTriangle*)(*iterPr))->intersect(ray, &near);
                        //((LSTriangle*)(*iterPr))->printInfo();
                        break;
                    case PLANERING:
                        ((LSPlaneRing*)(*iterPr))->intersect(ray, &near);
                        break;
                    default:
                        break;
                }
                if (isnan(near) == false) {
                    scene.raster.pixels[x + y*rasterWidth] = drawARGBColorFromFloatColor((*iterPr)->getLightColor(&scene, ray, near));
                }

            }
        }
  }
    
    CORasterSaveToBMP(&(scene.raster), "myImage.bmp");
    CORasterSaveToPPM(&(scene.raster), "myImage.ppm");
    printf("ray refract total: %i\n", ((LSSphere*)(*iterObj))->rayHitC);
    fclose(sceneFile);
    
    time(&end);
    timeCost = difftime(end, start);
    printf("It took %.2f sec to run the whole program.\n", timeCost);
    return 0;
}

