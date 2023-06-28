#include "shell.h"

/**
 * value_buff - buffers chained commands
 * @file: parameter struct
 * @buff: address of buffer
 * @build_history_list: take history list from lists
 * @len_add: address of len variable
 *
 * Return: bytes read
 */
ssize_t value_buff(file_t *file, char **buff, size_t *len_add)
{
	ssize_t a = 0;
	size_t len = 0;

	if (!*len_add)
	{
		
		free(*buff);
		*buff = NULL;
		signal(SIGINT, blockcontrolc);
#if USE_GETLINE
		a = get_line(buff, &len, stdin);
#else
		a = _getline(file, buff, &len);
#endif
		if (a > 0)
		{
			if ((*buff)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0';
				a--;
			}
			file->linecount_flag = 1;
			rm_comments(*buff);
			build_history_list(file, *buff, file->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len_add = a;
				file->cmd_buf = buff;
			}
		}
	}
	return (a);
}

/**
 * get_minus_new - gets a line minus the newline
 * @file: parameter
 * @check_chain: checks for argvs in the chain
 *
 * Return: bytes read
 */
ssize_t get__minus_new(file_t *file)
{
	static char *buff;
	static size_t a, b, len_add;
	ssize_t c = 0;
	char **buffer = &(file->arg), *p;

	_eputchar(BUF_FLUSH);
	a = value_buff(file, &buff, &len_add);
	if (c == -1) /* EOF */
		return (-1);
	if (len_add)
	{
		b = a;
		p = buff + a;

		check_chain(file, buff, &b, a, len_add);
		while (b < len_add)
		{
			if (check_chain(file, buff, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len_add)
		{
			a = len_add = 0;
			file->cmd_buf_type = CMD_NORM;
		}

		*buffer = p;
		return (_strlen(p));
	}

	*buffer = buff;
	return (c);
}

/**
 * read_buffer - reads a buffer
 * file: parameter
 * @buffer: buffer
 * @a: size
 *
 * Return: c
 */
ssize_t read_buffer(file_t *file, char *buff, size_t *a)
{
	ssize_t c = 0;

	if (*a)
		return (0);
	c = read(file->readfd, buff, READ_BUF_SIZE);
	if (c >= 0)
		*a = c;
	return (c);
}

/**
 * _get_next - gets the next line of input from STDIN
 * @file: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 * @_realloc: reallocates address
 * @_strcpy: copy len of a string
 * @_strcat: reads len of a string
 *
 * Return: s
 */
int _get_next(file_t *file, char **ptr, size_t *len)
{
	static char buff[READ_BUF_SIZE];
	static size_t a, longi;
	size_t d;
	ssize_t c = 0, f = 0;
	char *p = NULL, *new_p = NULL, *e;

	p = *ptr;
	if (p && longi)
		f = *len;
	if (a == longi)
		a = longi = 0;

	c = read_buffer(file, buff, &longi);
	if (c == -1 || (c == 0 && longi == 0))
		return (-1);

	e = _strchr(buff + a, '\n');
	d = e ? 1 + (unsigned int)(e - buff) : longi;
	new_p = _realloc(p, f, f ? f + d : d + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (f)
		_strcat(new_p, buff + a, d - a);
	else
		_strcpy(new_p, buff + a, d - a + 1);

	f += d - a;
	a = d;
	p = new_p;

	if (len)
		*len = f;
	*ptr = p;
	return (f);
}

/**
 * blockcontrolc - blocks ctrl-C
 * @signal: the signal number
 *
 * Return: void
 */
void blockcontrolc(__attribute__((unused))int signal)
{
	_eputs("\n");
	_eputs("$ ");
	_eputchar(BUF_FLUSH);
}
