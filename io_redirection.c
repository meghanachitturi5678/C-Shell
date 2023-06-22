#include "headers.h"

int file_stream(int f_d, int stream)
{
    if (f_d < 0)
    {
        printf(Bold Red "error in opening file!!\n" Default);
        return 0;
    }
    if (dup2(f_d, stream) < 0)
    {
        printf(Bold Red "error in redirecting!!\n" Default);
        return 0;
    }

    close(f_d);
}

int redir(int arg_count, char **argv)
{
    FILE *file;
    int fd, x = 0, n = 0;

    for (x = 0; x < arg_count; ++x)
    {
        if (strcmp(argv[x], "<") == 0 && x + 1 < arg_count)
        {
            ++x;
            fd = open(argv[x], O_RDONLY, 0644);
            file_stream(fd, STDIN_FILENO);
            continue;
        }
        else if (strcmp(argv[x], ">") == 0 && x + 1 < arg_count)
        {
            ++x;
            /*if (file=fopen(argv[x], "w"))
            {
                fd = fileno(file);
                fclose(file);
            }
            else*/
            fd = open(argv[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            file_stream(fd, STDOUT_FILENO);
            continue;
        }
        else if (strcmp(argv[x], ">>") == 0 && x + 1 < arg_count)
        {
            ++x;
            /*if (file=fopen(argv[x], "a"))
            {
                fd = fileno(file);
                fclose(file);
            }
            else*/
            fd = open(argv[x], O_WRONLY | O_CREAT | O_APPEND, 0644);
            file_stream(fd, STDOUT_FILENO);
            continue;
        }
        else
        {
            strcpy(argv[n], argv[x]);
            ++n;
            continue;
        }
        return 0;
    }
    x = n;
    while (x < arg_count)
    {
        argv[x] = NULL;
        ++x;
    }

    return n;
}
