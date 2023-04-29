#include "runningapp.h"

bool RunningApp(char*& res, int& maxLength) {
    FILE *pipe = popen("apt-mark showmanual", "r");

    if (!pipe) {
        return false;
    }

    int length = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        concatenate(res,buffer,maxLength);
    }

    pclose(pipe);
    return true;
}