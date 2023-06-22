#include "headers.h"
void pwd_print()
{
    char pwd_path[100000];

    if (getcwd(pwd_path, sizeof(pwd_path)) == NULL)
        perror(Bold Orange "Error in implementing getcwd()!!" Default);

    else
        printf("%s\n", pwd_path);
}
