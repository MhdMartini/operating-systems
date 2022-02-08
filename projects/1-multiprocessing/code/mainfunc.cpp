
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

std::string getCmd(int cNum, int numExecs)
{
    /* return the command for each process from its number
    and the total number of test files */
    string cmd = "./test";
    cNum = ((cNum - 1) % numExecs) + 1;
    cmd += std::to_string(cNum);
    return cmd;
}
