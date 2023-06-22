#include "headers.h"

void sig(int arg_count, char **argv)
{
    int flag = 0, jobno = str_int(strlen(argv[1]), argv[1]), signo = str_int(strlen(argv[2]), argv[2]);
    if (arg_count != 3)
    {
        printf(Bold Red "sig error:inappropriate number of arguments!!\n" Default);
        return;
    }
    if (jobno < 1)
    {
        printf(Bold Red "sig error:invalid job number!!\n" Default);
        return;
    }
    if (signo < 1 || signo > 31)
    {
        printf(Bold Red "sig error:invalid signal number!!\n" Default);
        return;
    }

    for (int i = 0; i < njob; i++)
    {
        if (jobbs[i].index == jobno)
        {
            flag = 1;
            if (kill(jobbs[i].pid, signo) < 0)
            {
                printf(Bold Red "error in killing\n" Default);
                return;
            }
            break;
        }
    }

    if (!flag)
    {
        printf(Bold Red "no job with given job number and signal number!!\n" Default);
        return;
    }
}