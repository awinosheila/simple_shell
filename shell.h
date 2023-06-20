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
 * @env: copy of environment on the linked lists
 * @environ: modified environment
 * @line_count: the line count error
 * @err_num: the error code to check for exit
 * @fname: filename
 * @readfd: the file descriptor to read from
 * @arg: a string generated from getline arguments
 * @argv:an array of strings generated from arguments
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
	list_t *env;
	char *fname;
	int err_num;
	unsigned int line_count;
	char **environ;

} file_t;

#define FILE_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

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
int _new_env(file_t *);
int populate_env_list(file_t *);
int _rm_env(file_t *);
char *_getval_env(file_t *, const char *);
int env_builtin(file_t *);
list_t *add_node_last(list_t **, const char *, int);
size_t print_list_str(const list_t *);
char *starts_with(const char *, const char *);
size_t list_len(const list_t *);
size_t list_len(const list_t *);
void print_error(file_t *file, char *estr);
int err_a_to_i(char *s);
char *convert_atoi(long int num, int base, int no);
void rm_comments(char *buf);
int print_deci(int value, int fd);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void free_list(list_t **);

#endif
