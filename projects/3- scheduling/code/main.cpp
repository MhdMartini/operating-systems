#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <assert.h>
#include "simulate.h"

using namespace std;

int main(int argc, char *argv[])
{
    char *fileIn = argv[1];
    char *fileOut = argv[2];
    int interval = atoi(argv[3]);

    simulateFCFS(fileIn, fileOut, interval);

    return 0;
}