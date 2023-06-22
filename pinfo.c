#include "headers.h"

int str_int(int k, char *s)
{
    int n, digit;
    n = 0;

    for (int i = 0; i < k; i++)
    {
        digit = s[i] - '0';

        if (digit < 0 || digit > 9)
            return 0;

        n *= 10;
        n += digit;
    }

    if (n < 0)
        n = 0;
    return n;
}

void pinfo(int arg_count, char **argv)
{
    int n, x, flag_fg;
    pid_t pid;

    char exe[inputsize], status[inputsize], temp[inputsize], ex_path[inputsize];
    char flag1[inputsize], flag2[inputsize], m_path[inputsize], mem[inputsize];
    char *path;

    flag_fg = strcmp(flag1, flag2);

    if (arg_count == 1)
        pid = getpid();

    else if (arg_count == 2)
    {
        n = strlen(argv[1]);
        pid = str_int(n, argv[1]);
    }

    else
    {
        printf(Bold Red "pinfo error:Too many arguments for pinfo command!!\n" Default);
        return;
    }

    sprintf(status, "/proc/%d/stat", pid);
    sprintf(exe, "/proc/%d/exe", pid);
    FILE *fp = fopen(status, "r");

    if (!fp)
    {
        printf("process with %d pid does not exist!!\n" Default, pid);
        return;
    }

    fscanf(fp, "%s %s %s %s %s %s %s %s", flag1, temp, status, temp, temp, temp, temp, flag2);
    sprintf(m_path, "/proc/%d/statm", pid);
    fp = fopen(m_path, "r");

    if (!fp)
    {
        printf(Bold Red "Process with pid %d does not exist!!\n" Default, pid);
        return;
    }

    fscanf(fp, "%s", mem);

    printf("pid : %d\n", pid);
    printf("process Status : %s", status);

    if (flag_fg)
        printf("%s\n", "");
    else
        printf("%s\n", "+");

    printf("memory : %s {Virtual Memory}\n", mem);
    printf("executable Path : ");

    x = readlink(exe, ex_path, 1000);

    if (x == -1)
        printf("NULL\n");

    else
    {
        ex_path[x] = '\0';
        path = strstr(ex_path, shell_home);

        if (path == NULL)
            printf("~%s\n", ex_path);

        else
            printf("~%s\n", path + strlen(shell_home));
    }
    end = time(NULL);
    timetaken = (end - begin);
}