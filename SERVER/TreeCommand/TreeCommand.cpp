#include "./TreeCommand.h"

using namespace std;

// void concatenate(char*& res, const char* buf, int &maxLength) {
//     int length = strlen(res) + strlen(buf) + 1;
//     if (length > maxLength) {
//         maxLength = length;
//         char temp[maxLength];
//         strcpy(temp, res);
//         for (int i = 0; i < strlen(buf); i++) {
//             temp[i + strlen(res)] = buf[i];
//         }
//         temp[maxLength - 1] = '\0';
//         free(res);
//         res = (char*)malloc(maxLength * 2);
//         strcpy(res,temp);
//         maxLength += maxLength;
//     } else {
//         int idx = strlen(res);
//         for (int i = idx; i < length - 1; i++) {
//             res[i] = buf[i - idx];
//         }
//         res[length - 1] = '\0';
//     }
// }
void concatenate(char*& res, const char* buf, int &maxLength)
{
    if(strlen(res) + strlen(buf) + 1 > maxLength)
    {
        char temp1[strlen(res) + 2] = {0};
        strcpy(temp1 , res);

        int newSize = strlen(res) + strlen(buf) + 2;
        free(res);
        res = (char*)malloc(newSize);
        strcpy(res , temp1);
        maxLength = newSize;
    }

    strcat(res , buf);
}

void tree(char*& res, int& maxLength, char* path, int dashes, int spaces, int level) {
    DIR* dir = opendir(path);
    struct dirent* direntptr;
    char buff[3];

    while ((direntptr = readdir(dir)) != NULL) {
        if (strcmp(direntptr->d_name, ".") == 0 || strcmp(direntptr->d_name, "..") == 0) {
            continue;
        }

        char* newpath = (char*) malloc (strlen(path) +  strlen(direntptr->d_name) + 2);
        sprintf(newpath,"%s/%s",path,direntptr->d_name);
        strcpy(buff,"\n");
        concatenate(res,buff,maxLength);

        if (spaces > 0) {
            for (int lvl = 0; lvl < level; lvl++) {
                strcpy(buff,"|");
                concatenate(res,buff,maxLength);
                for (int sp = 0; sp < spaces; sp++) {
                    strcpy(buff," ");
                    concatenate(res,buff,maxLength);
                }
            }
        }

        strcpy(buff,"|-");
        concatenate(res,buff,maxLength);
        for (int place = 0; place < dashes; place++) {
            strcpy(buff,"-");
            concatenate(res,buff,maxLength);
        }

        if ((direntptr->d_type == DT_DIR) && (access(newpath, R_OK) == 0)) {
            concatenate(res,direntptr->d_name, maxLength);
            tree(res, maxLength, newpath, dashes, spaces, level + 1);
            free(newpath);
            continue;
        }

        struct stat buf;
        int r = lstat(newpath, &buf);

        if (S_ISLNK(buf.st_mode)) {
            concatenate(res,direntptr->d_name,maxLength);
            free(newpath);
            continue;
        }

        if (S_ISFIFO(buf.st_mode)) {
            concatenate(res,direntptr->d_name,maxLength);
            free(newpath);
            continue;
        }

        if (access(newpath, X_OK) == 0) {
            concatenate(res,direntptr->d_name,maxLength);
            free(newpath);
            continue;
        }

        if (access(newpath, R_OK) == -1) {
            concatenate(res,direntptr->d_name,maxLength);
            free(newpath);
            continue;
        }

        if (S_ISREG(buf.st_mode)) {
            concatenate(res,direntptr->d_name,maxLength);
            free(newpath);
            continue;
        }
    }

    closedir(dir);
}

bool TreeCommand(char* msg, char*& res, int& maxLength) {
    struct stat buf;
    int r = stat(msg,&buf);
    if (!S_ISDIR(buf.st_mode)) {
        return false;
    }

    char* path = realpath(msg, NULL);
    char buff[3];
    strcpy(buff,"\n");

    concatenate(res,buff,maxLength);
    concatenate(res, path, maxLength);
    tree(res, maxLength, path, 4, 5, 0);
    // cout << strlen(res) << "\n" << res << "\n";
    
    free(path);
    return true;
}