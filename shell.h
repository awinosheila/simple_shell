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
#include <signal.h>
#include <stddef.h>
 

extern char **environ;
/*
 * struct passfile - contains pseudo-arguements to pass into a function
 * @err_no: error code \to check for by exit command
 * @filed_t: file with arguments
 * @file_t another file
 * @status: return value of the last executed command
 */

/*======== builtin_more.c ========*/

/* prints the current environ */
void print_environ(data_of_program *data);

typedef struct passfile
{
        int err_no;
        char *arg;
        char **argv;
        char path;
        int argc;
	int status;
	int readfd;
	int (*function)(data_of_program *data);
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
int builtin_locate(data_of_program *data);
int builtin_set_locate(data_of_program *data);
int builtin_unset_locate(data_of_program *data);
char **_copyenviron(void);
void free_environ(void);
char **_getenviron(const char *var);
char *get_location_file(file_t *file);
int write_location(file_t *file);
int read_location(file_t *file);
int build_location_list(file_t *file, char *buf, int linecount);
int renumber_location(file_t *file);
void *_realloc(void *p, unsigned int o, unsigned int n);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
#endif
