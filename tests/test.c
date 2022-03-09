#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a, b;

typedef struct
{
    int x, y;
} testArgs;

void *test(void *args)
{
    a = *(int *)args;
    b = *(int *)args;
    return 0;
}

void *test2(void *args)
{
    testArgs *my_args = args;
    a = my_args->x;
    b = my_args->y;
    free(my_args);
    return 0;
}

int main()
{
    // testArgs *args = malloc(sizeof *args);
    // args->x = 10;
    // args->y = 11;
    int num = 10;
    pthread_t t;
    pthread_create(&t, NULL, test, &num);
    pthread_join(t, NULL);
    printf("%d\n", a);
    printf("%d\n", b);
}
