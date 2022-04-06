/*
requests_simulator
    - reads and stores all requests from file
    - sorts the requests according to arrival time as a linked list
    - step method:
        returns a slice of the linked list for requests at time t


scheduler:
    - step:
        * steps the process at hand (if any)
        * accepts requests at t
    - accept_requests:
        *


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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <assert.h>
#include "process.h"
#include "requests.h"
#include "ready_que.h"

using namespace std;

int main(int argc, char *argv[])
{
    Process p(0, 12, 0, 1);
    return 0;
}