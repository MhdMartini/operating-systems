#ifndef PROCESS_H
#define PROCESS_H

extern int READY;
extern int RUNNING;
extern int FINISHED;

class Process
{
private:
    int id;   // process id
    int tb;   // burst time
    int ta;   // time of arrival
    int p;    // priority
    int taub; // remaining burst time

    int tw = 0;  // waiting time
    int tta = 0; // turnaround time

public:
    Process(int pid, int burstTime, int arrivalTime, int priority);
    void display();
    void wait();
    bool burst();
};

#endif