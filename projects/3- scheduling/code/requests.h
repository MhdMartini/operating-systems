#ifndef REQUESTS_H
#define REQUESTS_H

class Requests
{
private:
    char *fileIn;
    int t;

public:
    Requests(char *fileIn);
    void display();
};

#endif