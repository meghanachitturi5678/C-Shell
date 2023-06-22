#include "headers.h"

int cmp(const void *a, const void *b)
{
    job *j_1 = (job *)a;
    job *j_2 = (job *)b;
    return strcmp(j_1->jobName, j_2->jobName);
}

int flags(int arg_count, char **argv)
{
    if (arg_count > 3)
    {
        printf(Bold Red "jobs error:More number of arguments than acceptable!!\n" Default);
        return 0;
    }
    else if (arg_count == 3)
    {
        if (!strcmp(argv[1], "-r"))
        {
            if (!strcmp(argv[2], "-s"))
                return 3;

            else
            {
                printf(Bold Red "jobs error:invalid argument!!\n" Default);
                return 0;
            }
        }
    }
    else if (arg_count == 2)
    {
        if (!strcmp("-r", argv[1]))
            return 1;
        else if (!strcmp("-s", argv[1]))
            return 2;
        else
        {
            printf(Bold Red "jobs error:invalid argument!!\n" Default);
            return 0;
        }
    }
}

void jobs(int len, char **argv)
{
    int flag = 3;
    for (int i = 0; i < njob; i++)
        newarr[i] = jobbs[i];

    qsort(newarr, njob, sizeof(jobs), cmp);

    if (len > 1)
    {
        if ((flag = flags(len, argv)) == 0)
            return;
    }
    for (int i = 0; i < njob; i++)
    {

        if (flag == 3 || (flag == 1 && strcmp(newarr[i].stat, "Running") == 0) || (flag == 2 && strcmp(newarr[i].stat, "Stopped") == 0))
            printf("[%d] %s %s [%d]\n", newarr[i].index, newarr[i].stat, newarr[i].jobName, newarr[i].pid);
    }
}