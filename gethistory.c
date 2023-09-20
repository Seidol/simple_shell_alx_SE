#include "shell.h"

/**
 * get_history_file - Constructs the path for the history file.
 * @info: Parameter struct for shell information.
 *
 * Return: Allocated string containing the history file path.
 */

char *get_history_file(info_t *info)
{
	char *buf, *d;

	d = _getenv(info, "HOME=");
	if (!d)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, d);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Creates a new file or appends to an existing one
 * @info: Pointer to the parameter struct
 * Return: none
 * This function is responsible for creating a new file or appending
 * to an existing one. It takes a pointer to the parameter struct
 * as an argument. It returns 1 on successful operation, otherwise -1.
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filepath = get_history_file(info);
	list_t *node = NULL;

	if (!filepath)
		return (-1);

	fd = open(filepath, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filepath);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history from a file
 * @info: Pointer to the parameter struct
 * Return: 0
 * This function is responsible for reading the history from a file.
 * It takes a pointer to the parameter struct as an argument.
 * On successful operation,it returns the history count;otherwise,it returns 0.
 */

int read_history(info_t *info)
{
	int i, l = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

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
			build_history_list(info, buf + l, linecount++);
			l = i + 1;
		}
	if (l != i)
		build_history_list(info, buf + l, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to a history linked list
 * @info: Pointer to a structure containing
 * potential arguments. This is used to maintain
 *        a constant function prototype.
 * @buf: The buffer containing the history entry
 * @lt: The history line count (histcount)
 *
 * Return: always zoro
 * This function is responsible for adding a new entry to a linked
 * list that represents the command history. It takes a pointer to
 * therameter struct, the buffer containing the history entry,
 * and the line count. It always returns 0.
 */

int build_history_list(info_t *info, char *buf, int lt)
{
	list_t *n = NULL;

	if (info->history)
		n = info->history;
	add_node_end(&n, buf, lt);

	if (!info->history)
		info->history = n;
	return (0);
}

/**
 * renumber_history - Updates the numbering of the history
 * linked list after changes
 * @info: Pointer to a structure containing potential arguments.
 * This is used to maintain
 * a constant function prototype.
 *
 * This function is responsible for renumbering the history linked
 * list after any changes have been made. It takes a pointer to
 * the parameter struct. The function does not have a return value.
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
