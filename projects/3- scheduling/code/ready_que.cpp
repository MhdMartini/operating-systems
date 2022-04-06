#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "ready_que.h"

using namespace std;

class ReadyQue
{
public:
    char *fileIn; // name of input
};