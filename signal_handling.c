#include "headers.h"

void ctrlz(int sig)
{
    pid_t p = getpid();

    if (p != pid1)
        return;
    if (curr_pid != -1)
    {
        if (kill(curr_pid, SIGTSTP) == -1)
            return;

        strcpy(jobbs[njob].jobName, curr_job);
        jobbs[njob].index = njob+ 1;
        jobbs[njob].pid = curr_pid;
        jobbs[njob].fporbp = 1;
        strcpy(jobbs[njob].stat, "Stopped");
        ++njob;
    }
    return;
}

void ctrlc(int sig)
{
    pid_t p = getpid();
    if (p != pid1)
        return;
    if (curr_pid != -1)
    {
        if (kill(curr_pid, SIGINT) == -1)
            return;
    }
    return;
}
