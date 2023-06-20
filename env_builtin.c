#include "shell.h"

/**
 * _getval_env - gets the value of an environ variable
 * @file: Structure containing potential arguments. Used to maintain
 * @name: env varriable name
 *
 * Return: the value
 */
char *_getval_env(file_t *file, const char *name)
{
	list_t *node = file->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _new_env - Initialize a new environment variable,
 *             or modify an existing one
 * @file: containins potential arguments
 *  Return: Always 0
 */
int _new_env(file_t *file)
{
	if (file->argc != 3)
	{
		_eputs("reduce number of arguments\n");
		return (1);
	}
	if (_new_env(file, file->argv[1], file->argv[2]))
		return (0);
	return (1);
}

/**
 * _rm_env - Remove an environment variable
 * @file: containins potential arguments.
 * Return: Always 0
 */
int _rm_env(file_t *file)
{
	int a;

	if (file->argc == 1)
	{
		_eputs("add more arguments\n");
		return (1);
	}
	for (a = 1; a <= file->argc; a++)
		_rm_env(file, file->argv[a]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @file: containins potential arguments.
 * Return: Always 0
 */
int populate_env_list(file_t *file)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_last(&node, environ[a], 0);
	file->env = node;
	return (0);
}

/**
 * env_builtin - prints the current environment
 * @file: containins potential arguments
 * Return: Always 0
 */
int env_builtin(file_t *file)
{
        print_list_str(file->env);
        return (0);
}

