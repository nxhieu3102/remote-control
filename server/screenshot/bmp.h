#ifndef bmp_h
#define bmp_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(push, 1)
struct BITMAP_header
{
    char name[2];
    int32_t size;
    int32_t garbage;
    int32_t image_offset;

    void printbitmapheader() {
        printf("%s",name);
        printf("%d",size);
        printf("%d",garbage);
        printf("%d",image_offset);
    }
};
typedef struct BITMAP_header bitmap_header;

struct DIB_header
{
    int32_t header_size;
    int32_t width;
    int32_t height;
    int16_t colorplanes;
    int16_t bitsperpixel;
    int32_t compression;
    int32_t image_size;

    int32_t  m_xPixelsPreMeter;
    int32_t  m_yPixelsPreMeter;

    int32_t  m_colorsUsed;
    int32_t  m_colorsImportant;
};
typedef struct DIB_header dib_header;

struct Color
{
    int8_t blue;
    int8_t green;
    int8_t red;
};
typedef struct Color color;

struct Image
{
    int32_t height;
    int32_t width;
    color **rgb;
};
typedef struct Image image;
#pragma pack(pop)

#endif
