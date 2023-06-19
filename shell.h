#ifndef SHELL_H
#define SHELL_H

/*for read and write buffers*/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/*to convert numbers*/
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
 

extern char **environ;
/*
 * struct passfile - contains pseudo-arguements to pass into a function
 * @err_no: error code \to check for by exit command
 * @filed_t: file with arguments
 * @file_t another file
 * @status: return value of the last executed command
 */

typedef struct passfile
{
        int err_no;
        char *arg;
        char **argv;
        char path;
        int argc;
	int status;
	int readfd;
} file_t;

#define file_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

int is_interactive(file_t *filed);
int _delimeter(char c, char *delimeter);
int a_to_i(char *s);
int is_alpha(int c);
int exit_buitin(file_t *file);
void _eputs(char *);
int _eputchar(char);
int err_atoi(char *);
void print_error(file_t*, char *);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strstr(char *haystack, char *needle);
#endif
