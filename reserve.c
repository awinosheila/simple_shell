#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @p: A pointer to the memory allocated previously.
 * @o: The size in bytes of the allocated space for ptr.
 * @n: The size in bytes for the new memory block.
 *
 * Return: If n == o - p.
 *         If n == 0 and p is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *p, unsigned int o, unsigned int n)
{
	void *mem;
	char *p, *filler;
	unsigned int index;

	if (n == o)
		return (p);

	if (p == NULL)
	{
		mem = malloc(n);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (n == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}

	p_copy = p;
	mem = malloc(sizeof(*p_copy) * n);
	if (mem == NULL)
	{
		free(p);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < o && index < n; index++)
		filler[index] = *p_copy++;

	free(p);
	return (mem);
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Reads input from a stream.
 * @lineptr: A buffer to store the input.
 * @n: The size of lineptr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char *buffer = NULL;
	int c;

	if (input != 0)
		return (-1);

	fflush(stream);

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	for (input = 0; (c = getc(stream)) != EOF; input++)
	{
		if (input >= 120)
		{
			char *temp = realloc(buffer, input + 2);

			if (!temp)
			{
				free(buffer);
				return (-1);
			}
			buffer = temp;
		}

		buffer[input] = (char)c;
		if (c == '\n')
			break;
	}
	buffer[input] = '\0';
	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	input = 0;

	return (ret);
}
