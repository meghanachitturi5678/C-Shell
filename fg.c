#include "headers.h"

void fg(int arg_count, char **argv)
{
    int pid, status, flag = 0, jobno = str_int(strlen(argv[1]), argv[1]);

    if (arg_count != 2)
    {
        printf(Bold Red "fg error:inappropriate number of arguments!!\n" Default);
        return;
    }
    if (jobno < 1)
    {
        printf(Bold Red "fg error:invalid job number!!\n" Default);
        return;
    }

    for (int i = 0; i < njob; i++)
    {
        if (jobbs[i].index == jobno)
        {
            flag = 1;
            int pid = jobbs[i].pid;

            strcpy(curr_job, jobbs[i].jobName);
            curr_pid = pid;
            for (int j = i; j < (njob - 1); j++)
            {
                strcpy(jobbs[i].jobName, jobbs[i + 1].jobName);
                jobbs[i].pid = jobbs[i + 1].pid;
                jobbs[i].index = jobbs[i + 1].index;
                jobbs[njob].fporbp = 0;
            }
            --njob;
            waitpid(pid, &status, WUNTRACED);
            break;
        }
    }

    if (!flag)
    {
        printf(Bold Red "no job with given job number!!\n" Default);
        return;
    }
}