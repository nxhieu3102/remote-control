#include "./InstalledApp.h"

using namespace std;

bool getInstalledApp(char *&buffer)
{
    // system("apt-mark showmanual"); //list all the packages installed by users
    // system("sudo find / -type f -name \"*.sh\" -executable"); //list all file ".sh" ==> which files to install app
    // "apt-mark showmanual" //packages installed by users
    // "apt-mark showauto" //packages installed automatically

    //get installed apps
    // vector<string> packages;
    FILE *pipe = popen("apt-mark showmanual", "r");


    if (!pipe)
    {
        cerr << "Failed to run command\n";
        return 0;
    }

    char temp[300];
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