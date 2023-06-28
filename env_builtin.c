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
 * _new_env -starts a new environment variable,
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
	char *name = file->argv[1]; /* Get the name and value of the environment variable*/
	char *value = file->argv[2];

	size_t size = strlen(name) + strlen(value) + 2; /* Create a new string in the format "name=value"*/
	char *new_env = malloc(size);
	if (new_env == NULL)
	{
		_eputs("Failed to allocate memory\n");
		return (1);
	}
	snprintf(new_env, size, "%s=%s", name, value);
	
	/* Update the environment by adding/modifying the variable*/
	if (putenv(new_env) != 0)
	{
		_eputs("Failed to set environment variable\n");
		free(new_env);
		return (1)
	}

	/* Free the dynamically allocated memory*/
	free(new_env);

	return 0;
}

/**
 * _rm_env - Remove an environment variable
 * @file: containins potential arguments.
 * Return: Always 0
 */
int _rm_env(file_t *file)
{
if (file->argc != 2)
{
_eputs("reduce number of arguments\n");
return (1);
}

char *name = file->argv[1]; /* Get the name of the environment variable to remove*/

/* Call unsetenv to remove the variable*/
if (unsetenv(name) != 0)
{
	_eputs("Failed to remove environment variable\n");
	return (1);
}
{
return 0;
}

/**
 * populate_env_list - populates env linked list
 * @file: containins potential arguments.
 * Return: Always 0
 */
int populate_env_list(file_t *file)
{
	int a = 0;
	list_t *node = NULL;

	while (environ[a])
	{
		add_node_end(&node, environ[a], 0);
		a++;
	}
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

