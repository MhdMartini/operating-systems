#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"

#define INT_SIZE 4
#define BYTE_SIZE 8

#define LOG(x) std::cout << x << std::endl
#define LOGH(x) std::cout << std::hex << x << std::endl

int read(char *address)
{
    /* read four bytes from valid memory address as integer */
    uint8_t temp;
    int n = 0;
    for (int i = 0; i < INT_SIZE; i++)
    {
        temp = (uint8_t)address[i];
        n = (n << BYTE_SIZE) | temp;
    }
    return n;
}
void write(char *address, int value)
{
    /* write four bytes integer into valid memory address */
    int temp, n = 0;
    for (int i = INT_SIZE - 1; i > -1; i--)
    {
        temp = value & 0x0000FF;
        address[i] = (char)temp;
        value = value >> BYTE_SIZE;
    }
}
