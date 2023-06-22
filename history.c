#include "headers.h"
void history(int arg_count, char **argv)
{
    int x = 10;
    if (arg_count > 1)
    {
        printf(Red "Too many arguments for history command !!\n" Default);
        return;
    }
    if (nhist < 10)
        x = nhist;
    for (int i = 0; i < x; ++i)
        printf("%s\n", hist_cmds[i]);
    end = time(NULL);
    timetaken = (end - begin);
}
void add_hist(char *cmd)
{
    strcpy(hist_cmds[nhist % 20], cmd);
    ++nhist;
}
void write_hist()
{
    int x, y;
    FILE *fp = fopen(hist, "w");
    if (fp < 0)
    {
        perror(Bold Orange "Error in opening temporary file!!" Default);
    }
    x = nhist;
    if (x < 20)
        x = nhist;
    y = 0;
    while (y < x)
    {
        fprintf(fp, "%s\n", hist_cmds[y]);
        ++y;
    }
    fclose(fp);
}
