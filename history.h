#ifndef _HISTORY_H_
#define _HISTORY_H_

void add_hist(char *cmd);
void write_hist();
void history(int arg_count, char **argv);

#endif