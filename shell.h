#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>


/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct link - a struct thatlinking a commands name to a function 
 *
 *@order_name: command's name
 *@function: function executing the command
 */

typedef struct link
{
	char *order_name;
	void (*function)(char **order);
} command_link;

extern char **environ;
extern char *line;
extern char **commands;

void print(char *, int);
char **tkmaker(char *, char *);
void deleteline(char *);
int _lenght(char *);
void _copy(char *, char *);

int _compare(char *, char *);
char *_concat(char *, char *);
int _lensub(char *, char *);
int _countdiff(char *, char *);
char *_locchar(char *, char);

char *_tkstring(char *, char *, char **);
int _switchstr(char *);
void *memchange(void *pointer, unsigned int ancien, unsigned int nouveau);
void control_handl(int);
void delete_text(char *);

int desc_order(char *);
void launch_order(char **, int);
char *look(char *);
void (*retri(char *))(char **);
char *val_env(char *);

void env(char **);
void quit(char **);

extern void irresponsive(void);
extern void commence(char **current_token, int describe_token);

#endif
