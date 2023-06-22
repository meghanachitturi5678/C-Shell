#ifndef _MAIN_H
#define _MAIN_H

void die(const char *s);
void disableRawMode();
void enableRawMode();
void find_files(char* input,struct dirent *dir);
void autocompletion(char *final_prompt, char *cw_d, char *input);

char *getInput();
int redir_verify(char *token);
int pipe_verify(char *token);
void token_shellcommand(char *token);
void tokenize(char *input);

#endif