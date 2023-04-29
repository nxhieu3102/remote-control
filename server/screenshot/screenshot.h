#ifndef screenshot_h
#define screenshot_h

#include <stdio.h>
#include "bmp.h"
#include "../stringProcess.h"

image readImage(FILE *fs,dib_header dib);
void freeImage(image pic);
char* createfile(const char *file, int n);
void freeChar(char *fs);
//void CutBmp(const char *filebmp,int m,int n);
bool ScreenShot(const char* fileName, char*& res, int& maxLength);

#endif
