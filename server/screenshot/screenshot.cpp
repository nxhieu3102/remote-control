#include "screenshot.h"
#include "bmp.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
using namespace std;

image readImage(FILE *fs,dib_header dib)
{
    image pic;
    pic.rgb = new color * [dib.height*sizeof(color)];
    pic.height = dib.height;
    pic.width = dib.width;
    int bytestoread = (dib.bitsperpixel/8)*dib.width;
    int padding = dib.width%4;
    
    for(int i = dib.height-1; i>=0; i--)
    {
        pic.rgb[i] = new color [dib.width*sizeof(color)];
        fread(pic.rgb[i],bytestoread,1,fs);
        fseek(fs,padding,SEEK_CUR);
    }
    return pic;
}

void freeImage(image pic)
{
    for(int i = pic.height-1; i>=0; i--) delete[]pic.rgb[i];
    delete[]pic.rgb;
}

char* createfile(const char *file, int n)
{
    char *tmp = new char [strlen(file) + 2];
    int i = 0;
    while (i < strlen(file))
    {
        if (file[i] != '.') tmp[i] = file[i];
        else break;
        i++;
    }
    tmp[i] = (char)(n+48);
    tmp[i+1] = '\0';
    strcat(tmp,".bmp");
    return tmp;
}

void freeChar(char *fs)
{
    delete[]fs;
}

bool ScreenShot(const char* fileName, char*& res, int& maxLength) {
    FILE *fs = fopen(fileName, "rb");

    if (!fs) {
        return false;
    }
    printf("%s\n","hello");

    bitmap_header header;
    dib_header dib;
    fread(&header,sizeof(bitmap_header),1,fs);
    header.printbitmapheader();
    return true;
    // fread(&dib,sizeof(dib_header),1,fs);
    // fseek(fs,header.image_offset,SEEK_SET);
    // image bm = readImage(fs,dib);

    //concatenate(res, header.c_to_str(), )

}

// void CutBmp(const char *filebmp,int m,int n)
// {
//     FILE *fs = fopen(filebmp,"rb");
    
//     if (!fs)
//     {
//         printf( "Error cannot find\n" );
//         return;
//     }
    
//     bitmap_header header;
//     dib_header dib;
//     fread(&header,sizeof(bitmap_header),1,fs);
//     fread(&dib,sizeof(dib_header),1,fs);
//     fseek(fs,header.image_offset,SEEK_SET);
//     image bm = readImage(fs,dib);
    
//     if (m==0) m=1;
//     if (n==0) n=1;
//     dib.width/=n;
//     dib.height/=m;
    
//     int padding = (4-(3*dib.width)%4)%4;
    
//     int res = 0;
//     for(int cnt = 0; cnt < m; cnt++)
//     {
        
//         for (int pos = 0; pos < n; pos++)
//         {
//             char *file = strdup(createfile(filebmp,res+1));
//             FILE *fp = fopen(file,"wb");
            
//             fwrite(&header,1,sizeof(bitmap_header),fp);
//             fwrite(&dib,1,sizeof(dib_header),fp);
//             fseek(fp,header.image_offset,SEEK_SET);
//             for (int i = (m-cnt)*dib.height-1;i>=(m-cnt-1)*dib.height;i--)
//             {
//                 for(int j = pos*dib.width; j<(pos+1)*dib.width; j++)
//                 {
//                     fwrite(&bm.rgb[i][j],sizeof(color),1,fp);
//                 }
//                 fseek(fp,padding,SEEK_CUR);
//             }
//             res++;
//             freeChar(file);
//             freeChar(createfile(filebmp,res+1));
//             fclose(fp);
//         }
//     }
    
//     freeImage(bm);
//     fclose(fs);
// }

//g++ *.cpp treecommand/*.cpp runningprocess/*.cpp runningapp/*.cpp screenshot/*.cpp -o server