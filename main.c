#include "headers.h"
int b_g[2];
int common = 0;
char common_f[1000][1000];

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void find_files(char *input, struct dirent *dir)
{
    struct stat buffer;
    char *path = getcwd(cw_d, sizeof(cw_d));
    strcat(path, "/");
    strcat(path, dir->d_name);

    if (stat(path, &buffer) != -1)
    {
        if (!S_ISDIR(buffer.st_mode))
        {
            if (strncmp(dir->d_name, input, strlen(input)) == 0)
            {
                strcpy(common_f[common], dir->d_name);
                ++common;
            }
        }
        else
        {
            if (dir->d_name[0] != '.')
            {
                if (strncmp(dir->d_name, input, strlen(input)) == 0)
                {
                    strcpy(common_f[common], dir->d_name);
                    strcat(common_f[common], "/");
                    ++common;
                }
            }
        }
    }
}

void autocompletion(char *final_prompt, char *cw_d, char *input)
{
    char *cmd_part = (char *)malloc(sizeof(char) * 1000);

    common = 0;
    int x = 0, y = 0, z = 0, i = 0;
    int char_cnt = 0;
    char temp;
    while (input[x] != '\0')
    {
        if (input[x] == ' ')
        {
            i = x;
        }
        ++x;
    }

    strcpy(cmd_part, &input[i + 1]);

    DIR *directory_input = opendir(cw_d);
    struct dirent *dir = readdir(directory_input);
    while (dir)
    {
        find_files(cmd_part, dir);
        dir = readdir(directory_input);
    }
    printf("\n");

    if (common == 1)
    {
        x = 0;
        i = 0;
        while (input[x] != '\0')
        {
            if (input[x] == ' ')
            {
                i = x;
            }
            ++x;
        }

        strcpy(&input[i + 1], common_f[0]);
        printf("%s %s", final_prompt, input);
    }
    else if (common > 1)
    {
        while (y < common)
        {
            printf("%s\n", common_f[y]);
            ++y;
        }
        y = 0;
        z = strlen(common_f[0]);
        for (y = 0; y < z; ++y)
        {
            for (int j = 0; j < common; ++j)
            {
                temp = common_f[0][y];
                if (temp != common_f[j][y])
                {
                    char_cnt = y;
                    j = common;
                    y = z;
                }
            }
        }

        while (input[i] != '\0')
        {
            if (input[i] == ' ')
            {
                i = x;
            }
            i++;
        }

        strncpy(&input[i + 1], common_f[0], char_cnt);
        printf("%s %s", final_prompt, input);
    }
}

char *getInput()
{
    char *input;

    input = malloc(sizeof(char) * inputsize);
    input_str = fgets(input, inputsize, stdin);

    input[strcspn(input, "\n")] = '\0';

    return input;
}

int redir_verify(char *token)
{
    char *redir_a, *redir_i, *redir_o;

    redir_a = strstr(token, ">>");
    redir_i = strstr(token, "<");
    redir_o = strstr(token, ">");

    if ((redir_i == NULL) && (redir_o == NULL) && (redir_a == NULL))
        return 0;
    else
        return 1;
}

int pipe_verify(char *token)
{
    char *pipe = strstr(token, "|");
    if (pipe)
    {
        return 1;
    }
    return 0;
}

void token_shellcommand(char *token)
{
    char *argv[inputsize], *p;
    int arg_count = 0;
    int count, file_ret, flag = 0;
    int stdi = dup(STDIN_FILENO), stdo = dup(STDOUT_FILENO);

    if (pipe_verify(token))
    {
        apply_pipe(token, stdi, stdo);
        return;
    }

    if (redir_verify(token))
        flag = 1;

    if ((p = strtok_r(token, " \t\r", &token)) != NULL)
    {
        argv[arg_count] = p;
        ++arg_count;
    }
    while ((p = strtok_r(NULL, " \t\r", &token)) != NULL)
    {
        argv[arg_count] = p;
        ++arg_count;
    }
    if (flag)
        arg_count = redir(arg_count, argv);

    if (arg_count)
        shell_command(arg_count, argv, b_g);
    else
        return;

    file_ret = file_stream(stdo, STDOUT_FILENO);
    if (!file_ret)
        file_ret = file_stream(stdi, STDIN_FILENO);
}

void tokenize(char *input)
{
    char *token;

    int k = strlen(input);
    for (int i = 0; i < k; i++)
    {
        if (input[i] == '&')
        {
            b_g[0] = 1;
            i = k;
        }
    }
    while (token = strtok_r(input, ";&", &input))
        token_shellcommand(token);
}

/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
 */

int main()
{
    int x;
    char cmd[1000];
    char *input1 = malloc(sizeof(char) * inputsize);
    char *input2 = malloc(sizeof(char) * inputsize);
    nhist = 0;
    npro = 0;
    char c;
    char *inp = malloc(sizeof(char) * inputsize);
    if (getcwd(shell_home, sizeof(shell_home)) == NULL)
        perror(Bold Orange "Error in implementing getcwd!!");
    else
    {
        strcpy(hist, shell_home);
        strcat(hist, "/history.txt");
        FILE *fp = fopen(hist, "r");
        if (fp)
        {
            char cmd[1000] = "";

            while (fgets(cmd, sizeof(cmd), fp))
            {
                cmd[strcspn(cmd, "\n")] = 0;

                if (nhist)
                {
                    strcpy(hist_cmds[nhist - 1], cmd);
                    ++nhist;
                }

                else
                {
                    nhist = 1;
                }
            }
            --nhist;
            fclose(fp);
        }
        curr_pid = -1;
        pid1 = getpid();

        signal(SIGTSTP, ctrlz);
        signal(SIGINT, ctrlc);
        // signal(SIGQUIT,ctrld);

        b_g[0] = 0;
        b_g[1] = 0;
        print = 0;
        while (!feof(stdin))
        {
            setbuf(stdout, NULL);
            enableRawMode();

            shell_prompt(b_g[1]);
            timetaken = 0.0;

            b_g[0] = 0;
            b_g[1] = 0;
            //input2 = getInput();
            memset(inp, '\0', 100);
            int pt = 0;
            while (read(STDIN_FILENO, &c, 1) == 1)
            {
                if (iscntrl(c))
                {
                    if (c == 10)
                        break;
                    else if (c == 27)
                    {
                        char buf[3];
                        buf[2] = 0;
                        if (read(STDIN_FILENO, buf, 2) == 2)
                        { // length of escape code
                            printf("\rarrow key: %s", buf);
                        }
                    }
                    else if (c == 127)
                    { // backspace
                        if (pt > 0)
                        {
                            if (inp[pt - 1] == 9)
                            {
                                for (int i = 0; i < 7; i++)
                                {
                                    printf("\b");
                                }
                            }
                            inp[--pt] = '\0';
                            printf("\b \b");
                        }
                    }
                    else if (c == 9)
                    { // TAB character
                        getcwd(cw_d, sizeof(cw_d));
                        autocompletion(prompts, cw_d, inp);
                        pt = strlen(inp);
                    }
                    else if (c == 4)
                    {
                        exit(0);
                    }
                    else
                    {
                        printf("%d\n", c);
                    }
                }
                else
                {
                    inp[pt++] = c;
                    printf("%c", c);
                }
            }
            disableRawMode();
            strcpy(input2, inp);
            printf("\nInput Read: [%s]\n", inp);
            if (strcmp(input1, input2) != 0)
                add_hist(input2);
            tokenize(input2);
            printf("\r");
            strcpy(input1, input2);
            for (int i = 0; i < njob; i++)
            {
                if (!(strcmp(jobbs[i].stat, "Running")) && jobbs[i].fporbp == 1 && jobbs[i].print == 0)
                {

                    pid_t return_pid = waitpid(jobbs[i].pid, &status, WNOHANG);
                    if (return_pid == jobbs[i].pid)
                    {
                        strcpy(jobbs[i].stat, "Stopped");
                        printf("\n%s with pid %d exited normally\n", jobbs[i].jobName, jobbs[i].pid);
                        jobbs[i].print = 1;
                    }
                    else if (return_pid == -1)
                    {
                        strcpy(jobbs[i].stat, "Stopped");
                        printf("\n%s with pid %d exited abnormally\n", jobbs[i].jobName, newarr[i].pid);
                        jobbs[i].print = 1;
                    }
                }
            }
        }
    }

    return 0;
}
