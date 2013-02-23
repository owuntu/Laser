//I am modified from image.c

#include "image.h"
#include "LSColor.h"
#include <stdio.h>
void CORasterSaveToPPM(LSRaster* raster, char* path)
{
    // Open a file for writing
    FILE* f = fopen(path, "w");
    if (f == NULL)
    {
        printf("PPM couldn't open file %s for writing\n", path);
        return;
    }
    
    int rasterWidth = raster->getWidth();
    int rasterHeight = raster->getHeight();
    // Write out information required by plain PPM header definition
    fprintf(f, "P3\n");
    fprintf(f, "%i %i\n", rasterWidth, rasterHeight);
    fprintf(f, "%i\n", 255);
    
    // Write out pixel information
    LSColorARGB* rasterColor = raster->pixels;
    for (int y = 0; y < rasterHeight; y++)
    {
        for (int x = 0; x < rasterWidth; x++)
        {
            LSColorARGB color = *rasterColor;
            LSColorChannelByte red = (LSColorChannelByte)((color & 0x00FF0000) >> 16);
            LSColorChannelByte green = (LSColorChannelByte)((color & 0x0000FF00) >> 8);
            LSColorChannelByte blue = (LSColorChannelByte)((color & 0x000000FF) >> 0);
            fprintf(f, "%i ", red);
            fprintf(f, "%i ", green);
            fprintf(f, "%i ", blue);
            rasterColor++;
        }
        fprintf(f, "\n");
    }
}

void CORasterSaveToBMP(LSRaster* raster, char* path)
{
    //BMP (Windows V3)
    //Offset    Size    Description
    //0         2       the magic number used to identify the BMP file: 0x42 0x4D (Hex code points for B and M in big-endian order)
    //2         4       the size of the BMP file in bytes
    //6         2       reserved; actual value depends on the application that creates the image
    //8         2       reserved; actual value depends on the application that creates the image
    //10        4       the offset, i.e. starting address, of the byte where the bitmap data can be found.
    //14        4       the size of this header (40 bytes)
    //18        4       the bitmap width in pixels (signed integer).
    //22        4       the bitmap height in pixels (signed integer).
    //26        2       the number of color planes being used. Must be set to 1.
    //28        2       the number of bits per pixel, which is the color samplesPerPixel of the image. Typical values are 1, 4, 8, 16, 24 and 32.
    //30        4       the compression method being used. See the next table for a list of possible values.
    //34        4       the image size. This is the size of the raw bitmap data (see below), and should not be confused with the file size.
    //38        4       the horizontal resolution of the image. (pixel per meter, signed integer)
    //42        4       the vertical resolution of the image. (pixel per meter, signed integer)
    //46        4       the number of colors in the color palette, or 0 to default to 2n.
    //50        4       the number of important colors used, or 0 when every color is important; generally ignored.
    
    //Open file for writing
    FILE* file = fopen(path, "w");
    if (file == NULL)
        return;
    
    int rasterWidth = raster->getWidth();
    int rasterHeight = raster->getHeight();
    LSColorARGB* rasterPixels = raster->pixels;
    //Define header data
    uint16_t magicNumber = 0x4D42;
    uint16_t reserved0 = 0;//0x4D41;
    uint16_t reserved1 = 0;//0x5454;
    uint32_t dataOffset = 54;
    uint32_t infoHeaderSize = 40;
    uint32_t width = rasterWidth;
    uint32_t height = rasterHeight;
    uint16_t colorPlanes = 1;
    uint16_t bitsPerPixel = 32;
    uint32_t compression = 0;
    uint32_t dataSize = width * height * bitsPerPixel / 8;
    uint32_t horizontalResolution = 2835;
    uint32_t verticalResolution = 2835;
    uint32_t paletteColorCount = 0;
    uint32_t importantPaletteColorCount = 0;
    uint32_t fileSize = 54 + dataSize;
    
    //Write BMP header (Windows V3, 32bbp)
    fwrite(&magicNumber, sizeof(magicNumber), 1, file);
    fwrite(&fileSize, sizeof(fileSize), 1, file);
    fwrite(&reserved0, sizeof(reserved0), 1, file);
    fwrite(&reserved1, sizeof(reserved1), 1, file);
    fwrite(&dataOffset, sizeof(dataOffset), 1, file);
    fwrite(&infoHeaderSize, sizeof(infoHeaderSize), 1, file);
    fwrite(&width, sizeof(width), 1, file);
    fwrite(&height, sizeof(height), 1, file);
    fwrite(&colorPlanes, sizeof(colorPlanes), 1, file);
    fwrite(&bitsPerPixel, sizeof(bitsPerPixel), 1, file);
    fwrite(&compression, sizeof(compression), 1, file);
    fwrite(&dataSize, sizeof(dataSize), 1, file);
    fwrite(&horizontalResolution, sizeof(horizontalResolution), 1, file);
    fwrite(&verticalResolution, sizeof(verticalResolution), 1, file);
    fwrite(&paletteColorCount, sizeof(paletteColorCount), 1, file);
    fwrite(&importantPaletteColorCount, sizeof(importantPaletteColorCount), 1, file);
    
    //Write BMP body (XXRRGGBB)
    for (int y =  0; y < rasterHeight; y++)
    {
        for (int x = 0; x < rasterWidth; x++)
        {
            LSColorARGB color = rasterPixels[y * rasterWidth + x];
            fwrite(&color, sizeof(color), 1, file);
        }
    }
    
    //Cleanup
    fclose(file);
}

