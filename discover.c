#include "headers.h"
void hidfd(char *path, int d, int f)
{
    DIR *di;
    struct dirent *dir;
    struct stat info;
    char temp[inputsize];
    if ((di = opendir(path)) == NULL)
    {
        if (access(path, F_OK))
        {
            printf(Bold Red "cannot access %s!!\n" Default, path);
            return;
        }
    }
    while (dir = readdir(di))
    {
        if (dir->d_name[0] == '.')
            continue;
        sprintf(temp, "%s/%s", path, dir->d_name);
        stat(temp, &info);
        if (S_ISDIR(info.st_mode))
        {
            if (d)
                printf("%s\n", temp);
            hidfd(temp, d, f);
        }
        if (f && !(S_ISDIR(info.st_mode)))
        {
            printf("%s\n", temp);
        }
        sprintf(temp, "%s/%s", path, dir->d_name);
        stat(temp, &info);
        // if (S_ISDIR(info.st_mode))
    }
    closedir(di);
    return;
}
void discover(int arg_count, char **argv)
{
    struct dirent *dir;
    struct stat info;
    int flag_d = 0, flag_f = 0, k = 0;
    char path[inputsize];
    if (arg_count == 1)
    {
        strcpy(path, shell_home);
        hidfd(path, 1, 1);
    }
    else
    {
        if (arg_count == 2 && (strcmp(argv[1], "-d") != 0) && (strcmp(argv[1], "-f") != 0))
        {
            if (argv[1][0] == '.' && (strcmp(argv[1], "..") != 0))
            {
                getcwd(path, sizeof(path));
            }
            else if (argv[1][0] == '~')
            {
                strcpy(path, shell_home);
            }
            else if (strcmp(argv[1], "..") == 0)
            {
                chdir("..");
                getcwd(path, sizeof(path));
                chdir(shell_home);
            }
            else
            {
                if (chdir(argv[1]) == 0)
                    chdir(argv[1]);
                else if (chdir(argv[1]) == -1)
                {
                    printf(Bold Red "cd error: No Such File or Directory!!\n" Default);
                    k = 1;
                }
                getcwd(path, sizeof(path));
                chdir(shell_home);
            }
            flag_d = 1;
            flag_f = 1;
        }
        for (int i = 1; i < arg_count; i++)
        {

            if (strcmp(argv[i], "-d") == 0)
            {
                flag_d = 1;
            }
            else if (strcmp(argv[i], "-f") == 0)
            {
                flag_f = 1;
            }
            else
            {
                if (argv[i][0] == '.' && (strcmp(argv[i], "..") != 0))
                {
                    getcwd(path, sizeof(path));
                }
                else if (argv[i][0] == '~')
                {
                    strcpy(path, shell_home);
                }
                else if (strcmp(argv[i], "..") == 0)
                {
                    chdir("..");
                    getcwd(path, sizeof(path));
                    chdir(shell_home);
                }
                else
                {
                    if (chdir(argv[i]) == 0)
                        chdir(argv[i]);
                    else if (chdir(argv[i]) == -1)
                    {
                        printf(Bold Red "cd error: No Such File or Directory!!\n" Default);
                        k = 1;
                    }
                    getcwd(path, sizeof(path));
                    chdir(shell_home);
                }
            }
        }
        if (k == 0)
            hidfd(path, flag_d, flag_f);
    }
}