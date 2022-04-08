#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "scheduler.h"

using namespace std;

void simulate(char *fileIn, char *fileOut, int interval)
{
    Requests reqQue(fileIn);
    FCFS fcfs(&reqQue);
    Scheduler sch(&fcfs);

    FILE *fp = fopen(fileOut, "a");

    Process *currP = NULL;
    Process *lastP = NULL;
    while (!sch.step())
    {
        fprintf(fp, "t = %d\n", sch.rQ->reqQue->t - 1);

        lastP = currP;
        currP = sch.currProcess;

        if (lastP != currP)
        {
            // loading / finishing / preempting
            if (lastP == NULL)
            {
                // loading
                fprintf(fp, "CPU: Loading process %d (CPU burst = %d)\n", currP->id, currP->tb);
            }
            else
            {
                // finishing / preempting
                if (lastP->taub > 0)
                {
                    // preempting
                    fprintf(fp, "CPU: Preempting process %d (remaining CPU burst = %d); ", lastP->id, lastP->taub);
                    fprintf(fp, "loading process %d (CPU burst = %d)\n", currP->id, currP->tb);
                }
                else
                {
                    // finishing
                    fprintf(fp, "CPU: Finishing process %d (remaining CPU burst = %d); ", lastP->id, lastP->taub);
                    fprintf(fp, "loading process %d (CPU burst = %d)\n", currP->id, currP->tb);
                }
            }
        }
        else
        {
            // running
            fprintf(fp, "CPU: Running process %d (remaining CPU burst = %d)\n", currP->id, currP->taub + 1);
        }
        fprintf(fp, "\n");
    }
    sch.display();
    fclose(fp);
}