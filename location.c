#include "shell.h"

/**
 * get_location__file - retrieves the location of the file
 * @file: parameter struct
 *
 * Return: allocated string containing the location of the file else 0
 */
char *get_location_file(file_t *file)
{
	char *buf, *dir;

	dir = _getenv(file, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(LOCATE_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, LOCATE_FILE);
	return (buf);
}

/**
 * write_location - creates a file, or affixes to an existing file
 * @file: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_location(file_t *file)
{
	ssize_t fd;
	char *filename = get_location_file(file);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = file->location; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_location - reads content of a file specified by the file parameter.
 * @file: the parameter struct
 *
 * Return: locatecount on success, 0 otherwise
 */
int read_location(file_t *file)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_location_file(file);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_location_list(file, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_location_list(info, buf + last, linecount++);
	free(buf);
	file->locatecount = linecount;
	while (file->locatecount-- >= LOCATE_MAX)
		delete_node_at_index(&(file->location), 0);
	renumber_location(file);
	return (file->locatecount);
}

/**
 * build_location_list - adds entry to a location linked list
 * @file: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the location linecount, locatecount
 *
 * Return: Always 0
 */
int build_location_list(file_t *file, char *buf, int linecount)
{
	list_t *node = NULL;

	if (file->location)
		node = file->location;
	add_node_end(&node, buf, linecount);

	if (!file->location)
		file->location = node;
	return (0);
}

/**
 * renumber_location - renumbers the location linked list after changes
 * @file: Structure containing potential arguments. Used to maintain
 *
 * Return: the new locatecount
 */
if (!filename)
	return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
if (fd == -1)
	return (0);
if (!fstat(fd, &st))
	fsize = st.st_size;
if (fsize < 2)
	return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
	return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
if (rdlen <= 0)
	return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
	if (buf[i] == '\n')
{
	buf[i] = 0;
	build_location_list(file, buf + last, linecount++);
	last = i + 1;
}
if (last != i)
	build_location_list(info, buf + last, linecount++);
	free(buf);
	file->locatecount = linecount;
while (file->locatecount-- >= LOCATE_MAX)
	delete_node_at_index(&(file->location), 0);
	renumber_location(file);
	return (file->locatecount);
int renumber_location(file_t *file)
{
	list_t *node = file->location;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (file->locatecount = i);
}
