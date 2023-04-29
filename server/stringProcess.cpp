#include "stringProcess.h"

void concatenate(char*& res, const char* buf, int &maxLength) {
    int length = strlen(res) + strlen(buf) + 1;
    if (length > maxLength) {
        maxLength = length;
        char temp[maxLength];
        strcpy(temp, res);
        for (int i = 0; i < strlen(buf); i++) {
            temp[i + strlen(res)] = buf[i];
        }
        temp[maxLength - 1] = '\0';
        free(res);
        res = (char*)malloc(maxLength * 2);
        strcpy(res,temp);
        maxLength += maxLength;
    } else {
        int idx = strlen(res);
        for (int i = idx; i < length - 1; i++) {
            res[i] = buf[i - idx];
        }
        res[length - 1] = '\0';
    }
}