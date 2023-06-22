#include "headers.h"

void apply_pipe(char *token, int stdi, int stdo)
{
    int f_d[2], x = 0, n = 0;
    char *temp,*arg[inputsize];
    temp = strtok_r(token, "|", &token);
    
    while (temp)
    {
        arg[n] = temp;
        temp = strtok_r(NULL, "|", &token);
        ++n;
    }

    for(int x=0;x<n-1;++x)
    {
        if (pipe(f_d) < 0)
        {
            perror(Bold Orange "error in piping the commands!!" Default);
            return;
        }

        file_stream(f_d[1], STDOUT_FILENO);
        tokenize(arg[x]);
        file_stream(f_d[0], STDIN_FILENO);
    }

    file_stream(stdo, STDOUT_FILENO);
    tokenize(arg[n - 1]);
    file_stream(stdi, STDIN_FILENO);
}