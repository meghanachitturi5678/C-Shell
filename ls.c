#include "headers.h"
//Red for directories,green for files,white for executables
static int myCompare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void list_files(char *path, char *name)
{
    struct stat info;
    char date[50];
    int r = 0, g = 0, y = 0;
    if (stat(path, &info) == -1)
    {
        printf(Bold Red "error in getting info of file %s !!\n" Default, name);
        return;
    }
    if (S_ISDIR(info.st_mode))
    {
        printf("d");
        r = 1;
    }
    else
        printf("-");

    if (info.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if (info.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if (info.st_mode & S_IXUSR)
    {
        printf("x");
        y = 1;
    }
    else
        printf("-");
    if (info.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    if (info.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if (info.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");
    if (info.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if (info.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if (info.st_mode & S_IXOTH)
        printf("x ");
    else
        printf("- ");

    printf("%ld ", info.st_nlink);

    struct passwd *pw = getpwuid(info.st_uid);
    struct group *gr = getgrgid(info.st_gid);
    printf("%s ", pw->pw_name);
    printf("%s ", gr->gr_name);
    printf("%ld ", info.st_size);

    struct tm prev_time, curr_time;
    time_t curr = time(0);
    localtime_r(&info.st_mtime, &prev_time);
    localtime_r(&curr, &curr_time);

    if ((prev_time.tm_year == curr_time.tm_year) && (prev_time.tm_mon >= (curr_time.tm_mon - 6)))
        strftime(date, 20, "%b %d %H:%M", localtime(&(info.st_ctime)));
    else
        strftime(date, 20, "%b %d  %Y", localtime(&(info.st_ctime)));
    printf("%s ", date);
    if (r)
        printf(Bold Red "%s\n" Default, name);
    else if (y)
        printf(Bold White "%s\n" Default, name);
    else
        printf(Bold Green "%s\n" Default, name);
}

void getFiles(int count, char *dir, int flag_l, int flag_a)
{
    int total, index, file, x;
    char name[inputsize], path[inputsize];
    DIR *dirs;
    char *strings[100];
    struct dirent *files;
    struct stat statt;
    struct stat info;
    lstat(dir, &statt);

    file = 1;
    if ((dirs = opendir(dir)) == NULL)
    {
        if (access(dir, F_OK))
        {
            printf(Bold Red "cannot access %s\n" Default, dir);
            return;
        }
        else
            file = 0;
    }
    if (file)
    {
        total = 0;
        index = 0;
        while (files = readdir(dirs))
        {
            if (files->d_name[0] == '.' && !flag_a)
                continue;
            sprintf(name, "%s/%s", dir, files->d_name);
            strings[index] = files->d_name;
            lstat(name, &statt);
            ++index;
            total += statt.st_blocks;
        }
        if (flag_l)
            printf("total %u\n", total / 2);
        qsort(strings, index, sizeof(const char *), myCompare);
        x = 0;
        while (x < index)
        {
            sprintf(path, "%s/%s", dir, strings[x]);
            if (flag_l)
                list_files(path, strings[x]);
            else
            {
                stat(path, &info);
                if (stat(path, &info) == -1)
                {
                    printf(Bold Red "error in getting info of file %s !!\n" Default, name);
                    return;
                }
                if (S_ISDIR(info.st_mode))
                    printf(Bold Red "%s ", strings[x]);
                else if (info.st_mode & S_IXUSR)
                    printf(Bold White "%s " Default, strings[x]);
                else
                    printf(Bold Green "%s " Default, strings[x]);
            }
            ++x;
        }

        if (!flag_l)
            printf("\n");
        closedir(dirs);
    }
    else if (flag_l)
        list_files(dir, dir);

    else
        printf(Bold Red "%s\n", dir);
    end = time(NULL);
    timetaken = (end - begin);
}

void ls(int arg_count, char **argv)
{
    int l, flag_a, flag_l, count;
    char *dir[arg_count];
    count = 0;
    flag_a = 0;
    flag_l = 0;
    for (int i = 1; i < arg_count; i++)
    {
        l = strlen(argv[i]);
        if (l && argv[i][0] == '-')
        {
            for (int j = 0; j < l; j++)
            {
                if (argv[i][j] == 'l')
                    flag_l = 1;
                if (argv[i][j] == 'a')
                    flag_a = 1;
            }
        }
        else
        {
            if (strcmp(argv[i], "~") == 0)
                dir[count] = shell_home;

            else if (strcmp(argv[i], ""))
                dir[count] = argv[i];

            count++;
        }
    }
    if (count == 0)
        dir[0] = ".";

    for (int i = 0; i < (count + 1); i++)
    {
        if (i == count && i != 0)
            break;

        if (count > 1)
            printf(Bold Red "%s:\n" Default, dir[i]);

        getFiles(count, dir[i], flag_l, flag_a);

        if (count > 1)
            printf("\n");
    }
}