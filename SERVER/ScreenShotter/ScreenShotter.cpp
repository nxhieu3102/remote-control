#include "./ScreenShotter.h"

bool ScreenShot(char *&res , int &maxLength)
{
    const char *current_dir = ".";
    string file_path = current_dir + string("/shot.png");
    system(("gnome-screenshot --file=" + file_path).c_str());

    FILE *bmp_file = fopen("shot.png", "rb");
    if (!bmp_file)
    {
        return false;
    }

    // Read the contents of the BMP file into a buffer
    fseek(bmp_file, 0, SEEK_END);
    long file_size = ftell(bmp_file);

    fseek(bmp_file, 0, SEEK_SET);

    if(res != NULL)
        free(res);
    res = (char*)malloc(file_size);
    maxLength = file_size;

    printf("length of the file is %ld\n", file_size);
    fread(res, 1, file_size, bmp_file);

    // FILE *fd = fopen("output1.bmp","wb");
    // if (!fd) {
    //     printf("Can't open output.bmp\n");
    // }
    // fwrite(bmp_data,sizeof(unsigned char),file_size,fd);

    // fclose(fd);
    fclose(bmp_file);
    return true;
}
