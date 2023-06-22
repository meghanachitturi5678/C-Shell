#include "headers.h"
void process(int len, char **argv, int isBg)
{
    pid_t pid, wpid;
    pid = fork();
    if (pid < 0)
        perror(Bold Orange "error in executing fork!!\n");
    if (pid == 0)
    {
        ++npro;
        if (!isBg)
            argv[len] = NULL;
        else
            setpgid(0, 0);
        execvp(argv[0], argv);
        return;
    }
    else
    {
        if (!isBg)
        {
            wpid = waitpid(pid, &status, WUNTRACED);
            curr_pid = pid;
            strcpy(curr_job, argv[0]);

            for (int i = 1; i < len; i++)
            {
                strcat(curr_job, " ");
                strcat(curr_job, argv[i]);
                //strcat(jobs[njob].jobName," ");
                //strcat(jobs[njob].jobName, argv[i]);
            }
        }
        else
        {
            printf("[%d] %d\n", npro, pid);
            ++npro;
            pid1 = pid;
            print = 1;
            strcpy(bpro, argv[0]);
            strcpy(jobbs[njob].jobName, argv[0]);

            for (int i = 1; i < len; i++)
            {
                strcat(jobbs[njob].jobName, " ");
                strcat(jobbs[njob].jobName, argv[i]);
            }
            jobbs[njob].index = njob + 1;
            jobbs[njob].pid = pid;
            jobbs[njob].print = 0;
            jobbs[njob].fporbp = 1;
            //pid_t return_pid = waitpid(jobs[njob].pid, &status, WNOHANG);
            //if (return_pid == jobs[njob].pid)
            //    strcpy(jobs[njob].stat, "Stopped");
            //else
            strcpy(jobbs[njob].stat, "Running");
            njob++;
        }
    }
    time_t end = time(NULL);
    timetaken = (end - begin);

    return;
}
