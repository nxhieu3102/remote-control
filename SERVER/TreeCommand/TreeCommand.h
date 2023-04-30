#ifndef tree_command_h
#define tree_command_h

#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
//#include <iostream>


#define DEFAULT "\x1b[0m"
#define RED "\x1b[31;1m"
#define GREEN "\x1b[32;1m"
#define YELLOW "\x1b[33;1m"
#define BLUE "\x1b[34;1m"
#define CYAN "\x1b[36;1m"

//void concatenate(char*& res, const char* buf, int &maxLength);
void tree(char*& res, int& maxLength, char* path, int dashes, int spaces, int level);
bool TreeCommand(char* msg, char*& res, int& maxLength);

#endif