#include "runningprocess.h"

bool RunningProcess(char*& res, int& maxLength) {
    FILE* pipe = popen("ps -ef | grep -v '\\[.*\\]'", "r");

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