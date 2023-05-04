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

bool startApp(char *&buffer , string appName)
{
    if(buffer != NULL)
        free(buffer);
    buffer = (char *)malloc(100 + 1);
    memset(buffer , 0 , sizeof buffer);

    string res = "";
    if(system(("which " + appName + " >/dev/null 2>&1").c_str()) == 0)
    {
        system((appName + " >/dev/null 2>&1 &").c_str());
        res = "Open " + appName + " sucessfully";
    }
    else if(system(("which gnome-" + appName + " >/dev/null 2>&1").c_str()) == 0)
    {
        system(("gnome-" + appName + " >/dev/null 2>&1 &").c_str());
        res = "Open " + appName + " sucessfully!";
    }
    else
        res = "can't open " + appName;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    cerr << res << "\n";
    strcpy(buffer , res.c_str());
    return 1;
}

bool stopApp(char *&buffer , string appName)
{
    if(buffer != NULL)
        free(buffer);
    buffer = (char *)malloc(100 + 1);
    memset(buffer , 0 , sizeof buffer);

    string res = "";
    if(system(("killall " + appName).c_str()) == 0)
        res = "Stop " + appName + " sucessfully";
    else
        res = "Can't find " + appName;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    cerr << res << "\n";
    strcpy(buffer , res.c_str());
    return 1;
}

