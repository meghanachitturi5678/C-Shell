#include "headers.h"

void shell_prompt(int k)
{
    int x;
    char *ret;
    x = getlogin_r(username, sizeof(username));
    if (x != 0)
        perror(Bold Orange "Error in implementing getlogin_r!!" Default);
    x = gethostname(system_name, sizeof(system_name));
    if (x == -1)
        perror(Bold Orange "Error in implementing gethostname!!" Default);
    x = sprintf(prompt, Bold Green "<%s@%s" White ":", username, system_name);
    if (x < 0)
        perror(Bold Orange "Error in implementing sprintf!!" Default);

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        perror(Bold Orange "Error in implementing getcwd!!" Default);

    else
    {
        strcpy(prompts, prompt);
        if (k || timetaken < 1)
        {
            if (strcmp(current_dir, shell_home) == 0)
            {
                strcat(prompts, "~>");
                printf(White "%s~>", prompt);
            }
            else if (strstr(current_dir, shell_home))
            {
                strcat(prompts, "~");
                strcat(prompts, current_dir + strlen(shell_home));
                printf(White "%s~%s>" , prompt, current_dir + strlen(shell_home));
            }
            else
            {
                strcat(prompts, current_dir);
                printf(White "%s%s>", prompt, current_dir);
            }
        }
        else
        {
            if (strcmp(current_dir, shell_home) == 0)
            {
                strcat(prompts, "~");
                printf(White "%s~" Bold Yellow "took %ds>" Default, prompt, timetaken);
            }
            else if (strstr(current_dir, shell_home))
            {
                strcat(prompts, "~");
                strcat(prompts, current_dir + strlen(shell_home));
                printf(White "%s~%s" Bold Yellow " took %ds>" Default, prompt, current_dir + strlen(shell_home), timetaken);
            }
            else
            {
                strcat(prompts, current_dir);
                printf(White "%s%s" Bold Yellow " took %ds>" Default, prompt, current_dir, timetaken);
            }
        }
    }
}