#include "shell.h"

/*
 * _delimeter - checks if character is a delimeter
 * @c: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _delimeter(char c, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * a_to_i - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int a_to_i(char *s)
{
	int a, yes = 1, no = 0, integer;
	unsigned int final = 0;

	for (a = 0; s[a] != '\0' && no != 2; a++)
	{
		if (yes == -1)
			integer = -final;
		else
			integer = final;
	}

	{
		if (s[a] == '-')
			yes *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			no = 1;
			final *= 10;
			final += (s[a] - '0');
		}
		else if (no == 1)
			no = 2;
	}

	return (integer);
}

/**
 * is_interactive - returns true if shell is interactive mode
 * @filed: file descriptor
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int is_interactive(file_t *filed)
{
        return (isatty(STDIN_FILENO) && filed->readfd <= 2);
}
