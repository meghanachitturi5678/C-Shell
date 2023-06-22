#include "headers.h"

void bg(int arg_count, char **argv)
{
    int pid, flag = 0, jobno = str_int(strlen(argv[1]), argv[1]);

    if (arg_count != 2)
    {
        printf(Bold Red "bg error:inappropriate number of arguments!!\n" Default);
        return;
    }
    if (jobno < 1)
    {
        printf(Bold Red "bg error:invalid job number!!\n" Default);
        return;
    }

    for (int i = 0; i < njob; ++i)
    {
        if (jobbs[i].index == jobno)
        {
            flag = 1;
            pid = jobbs[i].pid;

            if (strcmp(jobbs[i].stat, "Stopped") == 0)
            {
                jobbs[i].print = 0;
                // pid_t return_pid = waitpid(jobs[i].pid, &status, WNOHANG);
                // if (return_pid == jobs[i].pid)
                //  strcpy(jobs[i].stat, "Stopped");
                //else
                strcpy(jobbs[i].stat, "Running");
            }
            break;
        }
    }
    if (!flag)
    {
        printf(Bold Red "no job with given job number!!\n" Default);
        return;
    }
}