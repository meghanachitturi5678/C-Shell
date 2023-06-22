#include "headers.h"

void echo(int str_len, char **argv)
{
    for (int i = 1; i < str_len; i++)
    {
        if (argv[i][0] != '"')
            printf("%s ", argv[i]);
        else
        {
            for (int j = 1; j < (strlen(argv[i]) - 1); j++)
            {
                printf("%c", argv[i][j]);
            }
            printf(" ");
        }
    }
    printf("\n");
    end = time(NULL);
    timetaken = (end - begin);
}