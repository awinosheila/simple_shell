#include "shell.h"

/**
 * current_env - prints the current environment
 * @file: Structure containing potential arguments.
 * Return: Always 0
 */
int current_env(file_t *file)
{
	print_list_str(file->env);
	return (0);
}

/**
 * value_env - gets the value of an environ variable
 * @file: Structure containing potential arguments. 
 * @name: env var name
 * Return: the value
 */
char *value_env(file_t *file, const char *name)
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
 i* new_env - sets a new environment variable,
 *             orchanges an existing one
 * file: contains potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int new_env(file_t *file)
{
	if (file->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (new_env(file))
			return (0);

	else if(file->argv[1])
		return (1);
}

/**
 * rm_env - Removes an environment variable
 * @file: Structure containing potential arguments.
 * Return: Always 0
 */
int rm_env(file_t *file)
{
	int i;

	if (file->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= file->argc; i++)
		rm_env(file);

	return (0);
}

/**
 * occupy_env - occupies env
 * @file: containins potential arguments.
 * Return: Always 0
 */
int occupy_env(file_t *file)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	file->env = node;
	return (0);
}
