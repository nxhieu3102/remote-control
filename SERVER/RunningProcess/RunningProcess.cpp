#include "./RunningProcess.h"

using namespace std;

bool getRunningProcess(char *&buffer)
{
    // system("ps -ef | grep -v '\\[.*\\]'"); //list all the running process
    //get running process
    vector<string> process;
    FILE *pipe = popen("ps -ef | grep -v '\\[.*\\]'", "r");

    if (!pipe)
    {
        cerr << "Failed to run command\n";
        return 0;
    }

    char temp[1024];
    string luu = "";
    while (fgets(temp, sizeof(temp), pipe) != NULL)
    {
        size_t len = strlen(temp);
        string s(temp, len);

        luu += s;
        memset(temp , 0 , sizeof temp);
        // std::this_thread::sleep_for(std::chrono::milliseconds(5)); // sleep to split the message
    }

    // cout << luu << "\n";

    int size = luu.size();
    
    if(buffer != NULL)
        free(buffer);
    buffer = (char *)malloc(size + 1);
    strcpy(buffer , luu.c_str());

    pclose(pipe);

    return 1;
}