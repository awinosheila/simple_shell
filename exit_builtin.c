#include "shell.h"

/**
 * exit_builtin - exits the shell
 * @file: contains arguments.
 * Return: exit if file.argv[0] != "exit"
 */
int exit_builtin(file_t *file)
{
	int exitcheck;

	if (file->argv[1])
	{
		exitcheck = err_atoi(file->argv[1]);
		if (exitcheck == -1)
		{
			file->status = 2;
			print_error(file, "Number not allowed: ");
			_eputs(file->argv[1]);
			_eputchar('\n');
			return (1);
		}
		file->err_no = err_atoi(file->argv[1]);
		return (-2);
	}
	file->err_no = -1;
	return (-2);
}
