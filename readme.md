**Assuming home directory is the directory which when executed starts shell**

**Run make main/make in folder containing makefile and then ./a.out to invoke the shell**

**Since suggested to write code in modular fashion,different .c,.h files were written for different specifications**

**headers.h**
  -includes required standard libraries,defined libraries,arrays used in all other .c files and info     for colours

**main.c**
  -contains code which calls for prompting the shell,take input,split it into tokens as required and call for implmenting corresponding command.And also contains code for Autocomplete.

**shellprompt.c**
  -prints the appropriate shell prompt at the instant

**shellcommand.c**
  -Calls the appropriate function for executing the command entered by user

**cd.c**
  -Contains function for executing different variants of cd command

**echo.c**
  -Contains function for executing echo command

**pwd_print.c**
  -Contains function for printing pwd at the instant the user enters this command

**ls.c**
   -Contains functions for executing ls command with different flags(multiple flags also)

**pinfo.c**
  -Contains function for printing process info(pinfo) as specified 

**sys_commands.c**
  -Contains functions for executing system commands with 2 variants as foreground and background and showing the exit status of background processes

**discover.c**
  -Contains functions for executing different variants of discover command as specified

**history.c**
  -Contains functions for writing history to file,extract it and print it in terminal if "history" command is entered

**io_redirection.c**
  -Contains function for required input/output redirection for corresponding commands

**pipeline.c**
  -Contains function for executing the command having "|"(pipe)

**I/O redirection along with command pipelines will also be executed properly using above two**

**jobs.c**
  -Contains function for execting "jobs" command

**fg.c**
  -Contains function for execting "fg" command

**bg.c**
  -Contains function for execting "bg" command

**signal.c**
  -Contains function for execting "sig" command

**signal_handling.c**
  -Contains function for handling signals "ctrl+z","ctrl+c"

**ctrl+d will be handled in main.c**

**Functions for autocompletion are written in main.c**

**Printing errors,exiting via perror are implemented when required**

**Errors for more arguments for a command was included**

**Colour coding is used for shell prompt,errors**

**Colour coding is used to differentiate between file names, directories and executables in the output of ls (Red for directories,Green for files,White for executables)**

**.h files(having function definitions of corresponding .c file) were written for .c files**

**In case of multiple foreground processes,time taken (if >=1sec) by recent foreground process gets printed in next prompt**
