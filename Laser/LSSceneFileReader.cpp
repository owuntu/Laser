//
//  LSSceneFileReader.cpp
//  Laser
//
//  Created by Ou Yuntao on 12-3-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "LSSceneFileReader.h"
#include <string.h>
#include "LSPrimitive.h"
#include "LSSphere.h"
#include "LSPlane.h"
#include "LSPlaneRing.h"
#include "LSTriangle.h"
#include <list.h>
using namespace std;
bool sceneFileReader(FILE* sceneFile, LSScene &scene)
{
    
    //Identify the scene file
    char c=' ';
    string s = "";
    c = fgetc(sceneFile);
    while (c != '\n' && c!= '\r') {
        s += c;
        c = fgetc(sceneFile);
    }
    if (!(s=="U5")) {
        printf("This is not a .urt scenefile");
        return 0;
    }
    
    scene.numOfLight=0;
    //FILE* sourceFile;   //.raw or .obj
    list<LSPrimitive*>::iterator iterObj;
    LSPrimitive* tempPrim;
    LSLight* testLight;
    
    //Get the raster width and height
    s = "";
    c = fgetc(sceneFile);
    while (c != '\n' && c!= '\r') {
        s += c;
        c = fgetc(sceneFile);
    }
    char* cstr;
    cstr = new char[s.size()+1];
    strcpy(cstr, s.c_str());
    char* tempEnd;
    char* tempEnd2;
    scene.rasterWidth = strtof(cstr, &tempEnd);
    scene.rasterHeight = strtof(tempEnd, NULL);
    scene.raster.setWidth(scene.rasterWidth);
    scene.raster.setHeight(scene.rasterHeight);
    scene.raster.newRaster();
    scene.raster.clear(LSColorFloat_Dark);
    delete cstr;
    //printf("width=%u, height=%u\n",rasterWidth, rasterHeight);
    s = "";
    c = fgetc(sceneFile);
    
    //Get camera information
    int lineCount = 0;
    while (lineCount<4) {
        s += c;
        c = fgetc(sceneFile);
        if (c == '\n' || c== '\r') {
            lineCount++;
        }
    }
    //ungetc(c, sceneFile);
    cstr = new char[s.size()+1];
    strcpy(cstr, s.c_str());
    scene.camera.setEyePoint(strtof(cstr, &tempEnd), strtof(tempEnd, &tempEnd2), strtof(tempEnd2, &tempEnd));
    scene.camera.setLookSpot(strtof(tempEnd, &tempEnd2), strtof(tempEnd2, &tempEnd), strtof(tempEnd, &tempEnd2));
    scene.camera.setUpVector(strtof(tempEnd2, &tempEnd), strtof(tempEnd, &tempEnd2), strtof(tempEnd2, &tempEnd));
    scene.camera.fieldOfViewAngleY = strtof(tempEnd, &tempEnd2);
    scene.camera.aspectRatio = strtof(tempEnd2, &tempEnd);
    delete cstr;
    
    s="";
    c=fgetc(sceneFile);
    while (c != '\n' && c!=EOF  && c!= '\r') {
        s += c;
        c = fgetc(sceneFile);
    }
    cstr = new char[s.size()+1];
    strcpy(cstr, s.c_str());
    scene.ambient.r = strtof(cstr, &tempEnd);
    scene.ambient.g = strtof(tempEnd, &tempEnd2);
    scene.ambient.b = strtof(tempEnd2, NULL);
    scene.ambient.a = 1.0f;
    delete cstr;

    int tempTriIndex = 0;
    
    //Get primitive
    while (c != EOF){
        s = "";
        c = fgetc(sceneFile);
        list<LSLight>::iterator iterTempL;
        switch (c) {

            // Get light information
            case 'l':
                c=fgetc(sceneFile);
                while (c != '\n' && c!=EOF && c!= '\r') {
                    s += c;
                    c = fgetc(sceneFile);
                }
                cstr = new char[s.size()+1];
                strcpy(cstr, s.c_str());
                testLight = new LSLight();
                testLight->myPosition->setX(strtof(cstr, &tempEnd));
                testLight->myPosition->setY(strtof(tempEnd, &tempEnd2));
                testLight->myPosition->setZ(strtof(tempEnd2, &tempEnd));
                testLight->myColor.r = strtof(tempEnd, &tempEnd2);
                testLight->myColor.g = strtof(tempEnd2, &tempEnd);
                testLight->myColor.b = strtof(tempEnd, NULL);
                testLight->myColor.a = 1.0f;
                testLight->myIndex = scene.numOfLight;
                scene.lightList.push_back(*testLight);
                //iterTempL = scene.lightList.end();
                //iterTempL--;
                //(*iterTempL).setLight(testLight.myColor, testLight.myPosition);
                scene.numOfLight++;
                delete cstr;
                break;
            
            //Sphere
            case 's':
                c=fgetc(sceneFile);
                while (c != '\n' && c!=EOF && c!= '\r') {
                    s += c;
                    c = fgetc(sceneFile);
                }
                cstr = new char[s.size()+1];
                strcpy(cstr, s.c_str());
                tempPrim = new LSSphere();
                ((LSSphere*)tempPrim)->setPrimitive(strtof(cstr, &tempEnd),     //x
                                                    strtof(tempEnd, &tempEnd2), //y
                                                    strtof(tempEnd2, &tempEnd), //z
                                                    strtof(tempEnd, &tempEnd2), //radius
                                                    strtof(tempEnd2, &tempEnd), //red
                                                    strtof(tempEnd, &tempEnd2), //green
                                                    strtof(tempEnd2, NULL));    //blue
                
                scene.objectList->push_back(tempPrim);
                delete cstr;
                break;

            // Plane
            case 'p':
                c=fgetc(sceneFile);
                while (c != '\n' && c!=EOF && c!= '\r') {
                    s += c;
                    c = fgetc(sceneFile);
                }
                cstr = new char[s.size()+1];
                strcpy(cstr, s.c_str());
                tempPrim = new LSPlane();
                ((LSPlane*)tempPrim)->setPrimitive(strtof(cstr, &tempEnd),     //x
                                                   strtof(tempEnd, &tempEnd2), //y
                                                   strtof(tempEnd2, &tempEnd), //z
                                                   strtof(tempEnd, &tempEnd2), //nx
                                                   strtof(tempEnd2, &tempEnd), //ny
                                                   strtof(tempEnd, &tempEnd2), //nz
                                                   LSColorFloatMake(255.0f, 
                                                        strtof(tempEnd2, &tempEnd), //color.r
                                                        strtof(tempEnd, &tempEnd2), //color.g
                                                        strtof(tempEnd2, NULL)));   //color.b

                scene.objectList->push_back(tempPrim);
                delete cstr;
                break;
                
            // Triangles
            case 't':
                c=fgetc(sceneFile);
                while (c != '\n' && c!=EOF) {
                    s += c;
                    c = fgetc(sceneFile);
                }
                cstr = new char[s.size()+1];
                strcpy(cstr, s.c_str());
                tempPrim = new LSTriangle();
                ((LSTriangle*)tempPrim)->setPrimitive(strtof(cstr, &tempEnd),     //x1
                                                      strtof(tempEnd, &tempEnd2), //y1
                                                      strtof(tempEnd2, &tempEnd), //z1
                                                      
                                                      strtof(tempEnd, &tempEnd2), //x2
                                                      strtof(tempEnd2, &tempEnd), //y2
                                                      strtof(tempEnd, &tempEnd2), //z2
                                                      
                                                      strtof(tempEnd2, &tempEnd), //x3
                                                      strtof(tempEnd, &tempEnd2), //y3
                                                      strtof(tempEnd2, &tempEnd), //z3
                                                      
                                                      strtof(tempEnd, &tempEnd2), //r
                                                      strtof(tempEnd2, &tempEnd), //g
                                                      strtof(tempEnd, NULL));     //b
                ((LSTriangle*)tempPrim)->_myIndex = tempTriIndex;
                tempTriIndex++;
                scene.objectList->push_back(tempPrim);
                delete cstr;
                break;
            //PlaneRing
            case 'r':
                c=fgetc(sceneFile);
                while (c != '\n' && c!=EOF) {
                    s += c;
                    c = fgetc(sceneFile);
                }
                cstr = new char[s.size()+1];
                strcpy(cstr, s.c_str());
                tempPrim = new LSPlaneRing();
                ((LSPlaneRing*)tempPrim)->setPrimitive(strtof(cstr, &tempEnd),     //ox
                                                       strtof(tempEnd, &tempEnd2), //oy
                                                       strtof(tempEnd2, &tempEnd), //oz
                                                       
                                                       strtof(tempEnd, &tempEnd2), //inR
                                                       strtof(tempEnd2, &tempEnd), //outR
                                                       
                                                       strtof(tempEnd, &tempEnd2), //nx
                                                       strtof(tempEnd2, &tempEnd), //ny
                                                       strtof(tempEnd, &tempEnd2), //nz
                                                       
                                                       strtof(tempEnd2, &tempEnd), //r
                                                       strtof(tempEnd, &tempEnd2), //g
                                                       strtof(tempEnd2, NULL));    //b
                scene.objectList->push_back(tempPrim);
                delete cstr;
                break;
            case '#':
                c=getc(sceneFile);
                while (c != '\n' && c != EOF && c!= '\r') {
                    c=fgetc(sceneFile);
                }
                break;
            default:
                break;
        }
    }
    return 1;
}