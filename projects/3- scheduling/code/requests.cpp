/* class to simulate incoming requests from processes */

#include <stdio.h>
#include <iostream>
// #include <fstream>
#include "requests.h"

using namespace std;

Requests::Requests(char *fileInput)
{
    fileIn = fileInput;
    display();
}

void Requests::display()
{
    cout << fileIn << endl;
}