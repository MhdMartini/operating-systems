#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include "utils.h"

#define LOG(x) std::cout << x << std::endl
#define LOGH(x) std::cout << std::hex << x << std::endl

using namespace std;

std::mutex lockFile, lockMMU, lockDisk, lockFault, lockAll;

int main(int argc, char *argv[])
{
    run(argv[1], argv[2]);
    return 0;
}