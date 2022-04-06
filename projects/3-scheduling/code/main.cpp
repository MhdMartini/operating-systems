#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "ready_que.h"

/*
have a (ready queue) which
    - is a linked list:
        * every time step includes the arriving processes
        * program over when no processes remain
        * it points to the process that should go next
    - when a condition happens (new process arrives, or quantum time ends),
    it changes its ordering according to the scheme:
        * RR - rotates left
        * others - enqueues the new process according to scheme (FCFS, SJF, etc.)
    - enqueues the processes according to arrival time.
    -
non-preemptive algorithms:
    when a process leaves the queue, it is gone forever
preemptive:
    when a process leaves the queue, the process will be enqueued back in
    if a new process arrives
*/

int main(int argc, char *argv[])
{
    printf("hello world\n");
    return 0;
}