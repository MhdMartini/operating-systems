#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "utils.h"
#include <mutex>

#define LOG(x) std::cout << x << std::endl
#define LOGH(x) std::cout << std::hex << x << std::endl

using namespace std;

std::mutex lockFile, lockMMU;

int main(int argc, char *argv[])
{
    run(argv[1]);
    return 0;
}