#include "shell.h"

/**
 * rm_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}

/**
 * err_a_to_i - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int err_a_to_i(char *s)
{
	int a = 0;
	unsigned long int final = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			final *= 10;
			final += (s[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @file: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(file_t *file, char *estr)
{
	_eputs(file->fname);
	_eputs(": ");
	print_d(file->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(file->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * convert_atoi - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @no: argument flags
 *
 * Return: string
 */
char *convert_atoi(long int num, int base, int no)
{
	static char *array;
	static char buffer[50];
	char yes = 0;
	char *ptr;
	unsigned long a = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		a = -num;
		yes = '-';
	}

	array = yes & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do      {
		--ptr = array[n % base];
		a /= base;
	}

	while (a != 0);

	if (sign)
		*--ptr = yes;
	return (ptr);
}

/**
 * print_deci - function prints a decimal (integer) number (base 10)
 * @value: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_deci(int value, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _abs_, new;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		new %= a;
	}
	__putchar('0' + new);
	count++;

	return (count);
}
