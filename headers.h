#ifndef _HEADERS_H
#define _HEADERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <grp.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <time.h>
#include <wait.h>
#include <termios.h>
#include <ctype.h>

#include "shellcommand.h"
#include "shellprompt.h"
#include "cd.h"
#include "pwd_print.h"
#include "echo.h"
#include "ls.h"
#include "main.h"
#include "pinfo.h"
#include "history.h"
#include "process.h"
#include "discover.h"
#include "io_redirection.h"
#include "pipeline.h"
#include "jobs.h"
#include "signal.h"
#include "fg.h"
#include "bg.h"
#include "signal_handling.h"

#define inputsize 1000

time_t begin,end;
pid_t pid1;

int timetaken,nhist,npro,status,print;
char username[inputsize], system_name[inputsize], current_dir[inputsize], prompt[10 * inputsize],prompts[10*inputsize];
char shell_home[inputsize],prev_dir[inputsize], curr_dir[inputsize],cw_d[inputsize];
char bpro[50],hist[inputsize],hist_cmds[20][inputsize];
char *input_str;

typedef struct Job
{
    int index,print,fporbp;
    char jobName[inputsize];
    pid_t pid;
    char stat[20];
} job;

job jobbs[50],newarr[50];
pid_t curr_pid;
char curr_job[inputsize];
int njob,bindex;

#define Red "\033[38;5;1m"
#define Green "\033[38;5;121m"
#define White  "\033[0;37m"
#define Orange "\033[38;5;209m"
#define Yellow "\033[38;5;223m"
#define Bold "\033[1m"
#define Default "\033[0m"

#endif
