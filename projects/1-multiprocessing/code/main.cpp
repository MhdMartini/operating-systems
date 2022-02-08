#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <map>
#include <iostream>
#include <unistd.h>
#include "mainfunc.h"

using namespace std;

int main(int argc, char *argv[])
{
    int nCProc = atoi(argv[1]); // number of child processes to be created
    pid_t pPid = getpid();      // get parent pid
    pid_t myPid;                // each child process saves its own pid here
    int myNum;                  // each child process saves its own number here
    std::map<pid_t, int> pidMap;

    cout << "Parent pid is " << pPid << endl;

    for (size_t i = 0; i < nCProc; i++)
    {
        if (getpid() == pPid)
        // parent
        {
            pid_t cPid = fork();
            if (cPid != 0)
            // parent again
            {
                cout << "Started child " << i + 1 << " with pid " << cPid << endl;
                pidMap.insert(std::pair<pid_t, int>(cPid, i + 1));
            }

            else
            // children
            {
                myNum = i + 1;
                std::string cmd = getCmd(myNum);
                const char *cmdCh = cmd.c_str();
                execlp(cmdCh, cmdCh, NULL);
            }
        }
    }

    // parent wait for all children to finish
    if (getpid() == pPid)
    {
        for (size_t i = 0; i < nCProc; i++)
        {
            pid_t cPid = wait(NULL);
            auto cNum = pidMap.find(cPid);
            cout << "Child " << cNum->second << " (PID " << cPid << ") finished" << endl;
        }
    }
}
