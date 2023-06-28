#ifndef SHELL_H
#define SHELL_H

/*for read and write buffers*/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

/*to convert numbers*/
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

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

typedef struct info
{
        char *program_name;
        char *input_line;
        char *command_name;
        int exec_counter;
        int file_descriptor;
        char **tokens;
        char **env;
        char **alias_list;
} data_of_program;

typedef struct builtin
{
	char *env_get_key;
	int env_set_key;
	char print_environ;
	char *str_duplicate;
	int env_remove_key;
} builtin_more;

extern char **environ;
/*
 * struct passfile - contains pseudo-arguements to pass into a function
 * @err_no: error code \to check for by exit command
 * @filed_t: file with arguments
 * @file_t another file
 * @status: return value of the last executed command
 * @env_get_key:command to get the environment key
 * @env_set_key: to set the environment key
 * @print_environ: prints the current environment
 * @str_duplicate: duplicates a string
 * env_remove_key: removes the environment key
 * @_print: print
 */

typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

typedef struct passfile
{
	char *arg;
	char **argv;
        char *path;
        int argc;
	unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        char **environ;
        int env_changed;
        int status;
        list_t *env;
        list_t *history;
        list_t *alias;

        char **cmd_buf;
        int cmd_buf_type;
        int readfd;
        int histcount;
} file_t;

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#define FILE_INIT {0, NULL, NULL, NULL, 0, 0, 0, 0}

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
void print_environ(data_of_program *data);
char *str_duplicate(char *string);
char *env_get_key(char *name, data_of_program *data);
int env_set_key(char *key, char *value, data_of_program *data);
int _print(char *string);
int env_remove_key(char *key, data_of_program *data);
int main(int ac, char **av);
int current_env(file_t *file);
char *value_env(file_t *file, const char *name);
int new_env(file_t *file);
int rm_env(file_t *file);
int occupy_env(file_t *file);
#endif
