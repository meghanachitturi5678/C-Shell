#include "headers.h"

void shell_command(int arg_count, char **argv, int b_g[2])
{
   
    begin = time(NULL);
    if (strcmp(argv[0], "echo") == 0)
        echo(arg_count, argv);

    else if (strcmp(argv[0], "cd") == 0)
        cd(arg_count, argv);

    else if (strcmp(argv[0], "pwd") == 0)
        pwd_print();

    else if (strcmp(argv[0], "ls") == 0)
        ls(arg_count, argv);

    else if (strcmp(argv[0], "pinfo") == 0)
        pinfo(arg_count, argv);

    else if (strcmp(argv[0], "history") == 0)
        history(arg_count, argv);
         else if (strcmp(argv[0], "discover") == 0)
        discover(arg_count, argv);
    else if (strcmp(argv[0], "jobs") == 0)
        jobs(arg_count, argv);
    else if (strcmp(argv[0], "sig") == 0)
        sig(arg_count, argv);
    else if (strcmp(argv[0], "fg") == 0)
        fg(arg_count, argv);
    else if (strcmp(argv[0], "bg") == 0)
        bg(arg_count, argv);
    
    else if (b_g[0])
    {
        process(arg_count, argv, 1);
        b_g[1]=1;
    }
    else
    {
        process(arg_count, argv, 0);
    }

    write_hist();
}
