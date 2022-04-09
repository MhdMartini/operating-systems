#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "scheduler.h"
#include <fstream>
using namespace std;

// void simulate(char *fileIn, char *fileOut, int interval)
// {
//     Requests reqQue(fileIn);
//     FCFS fcfs(&reqQue);
//     Scheduler sch(&fcfs);

//     FILE *fp = fopen(fileOut, "w");
//     fprintf(fp, "***** FCFS Scheduling *****\n");

//     Process *currP = NULL;
//     Process *lastP = NULL;
//     int t = 30;
//     bool done = false;
//     while (!sch.step())
//     {
//         t = sch.rQ->reqQue->t - 1;

//         lastP = currP;
//         currP = sch.currProcess;

//         if (t % interval)
//             continue;

//         fprintf(fp, "t = %d\n", t);
//         if (lastP != currP)
//         {
//             // loading / finishing / preempting
//             if (lastP == NULL)
//                 // loading
//                 fprintf(fp, "CPU: Loading process %d (CPU burst = %d)\n", currP->id, currP->tb);
//             else
//             {
//                 // finishing / preempting
//                 if (lastP->taub > 0)
//                 {
//                     // preempting
//                     fprintf(fp, "CPU: Preempting process %d (remaining CPU burst = %d); ", lastP->id, lastP->taub);
//                     fprintf(fp, "loading process %d (CPU burst = %d)\n", currP->id, currP->tb);
//                 }
//                 else
//                 {
//                     // finishing and loading
//                     fprintf(fp, "CPU: Finishing process %d; ", lastP->id);
//                     fprintf(fp, "loading process %d (CPU burst = %d)\n", currP->id, currP->tb);
//                 }
//             }
//         }
//         else
//             // running
//             fprintf(fp, "CPU: Running process %d (remaining CPU burst = %d)\n", currP->id, currP->taub + 1);
//         fprintf(fp, "\n");
//     }
//     fprintf(fp, "t = %d\n", ++t);
//     fprintf(fp, "CPU: Finishing process %d ", currP->id);

//     cout << "Good bye!" << endl;
//     fclose(fp);
// }

void simulate(char *fileIn, char *fileOut, int interval)
{
    Requests reqQue(fileIn);
    FCFS fcfs(&reqQue);
    Scheduler sch(&fcfs);

    ofstream myfile;
    myfile.open(fileOut);
    myfile << "***** FCFS Scheduling *****" << endl;

    Process *currP = NULL;
    Process *lastP = NULL;
    int t = 30;
    bool done = false;
    while (!sch.step())
    {
        t = sch.rQ->reqQue->t - 1;

        lastP = currP;
        currP = sch.currProcess;

        if (t % interval)
            continue;

        myfile << "t = " << t << endl;
        if (lastP != currP)
        {
            // loading / finishing / preempting
            if (lastP == NULL)
                // loading
                myfile << "CPU: Loading process " << currP->id << " (CPU burst = " << currP->tb << ")" << endl;
            else
            {
                // finishing / preempting
                if (lastP->taub > 0)
                {
                    // preempting
                    myfile << "CPU: Preempting process " << lastP->id << " (remaining CPU burst = " << lastP->taub << "); ";
                    myfile << "loading process " << currP->id << " (CPU burst = " << currP->tb << ")" << endl;
                }
                else
                {
                    // finishing and loading
                    myfile << "CPU: Finishing process " << lastP->id << "; ";
                    myfile << "loading process " << currP->id << " (CPU burst = " << currP->tb << ")" << endl;
                }
            }
        }
        else
            // running
            myfile << "CPU: Running process " << currP->id << " (remaining CPU burst = " << currP->taub + 1 << ")" << endl;
        myfile << endl;
    }
    myfile << "t = " << ++t << endl;
    myfile << "CPU: Finishing process " << currP->id << endl;

    cout << "Good bye!" << endl;
    myfile.close();
}