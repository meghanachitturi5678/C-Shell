#include "headers.h"

void cd(int arg_count, char **argv)
{
    int k, l;
    char temp[inputsize];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        perror(Bold Orange "Error in implementing getcwd!!" Default);

    else
    {
        if (arg_count == 1)
            chdir(shell_home);
        else if (arg_count > 2)
            printf(Bold Red "cd error:More number of arguments than acceptable!!\n" Default);

        else if (strcmp(argv[1], "~") == 0)
        {
            chdir(shell_home);
        }
        else if (argv[1][0] == '~')
        {
            k = strlen(shell_home);
            strcpy(temp, shell_home);
            l = strlen(argv[1]);
            for (int i = 0; i < l; i++)
            {
                temp[i + k] = argv[1][i + 1];
            }
            printf("%s\n", temp);
            if (chdir(temp) == 0)
                chdir(temp);
            else if (chdir(temp) == -1)
                printf(Bold Red "cd error: No Such File or Directory!!\n" Default);
        }
        else if (strcmp(argv[1], "-") == 0)
        {
            printf("%s\n", prev_dir);
            chdir(prev_dir);
        }
        else if (strcmp(argv[1], "..") == 0)
        {
            chdir("..");
        }

        else if (strcmp(argv[1], ".") == 0)
        {
            chdir(".");
        }
        else
        {
            if (chdir(argv[1]) == 0)
                chdir(argv[1]);
            else if (chdir(argv[1]) == -1)
                printf(Bold Red "cd error: No Such File or Directory!!\n" Default);
        }
    }
    strcpy(prev_dir, current_dir);
    end = time(NULL);
    timetaken = (end - begin);
}