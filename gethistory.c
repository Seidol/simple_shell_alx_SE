#include "shell.h"

/**
 * get_history_filepath - Constructs the path for the history file.
 * @info: Parameter struct for shell information.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_filepath(info_t *info)
{
	char *home_dir = _getenv(info, "HOME=");

	if (!home_dir)
		return (NULL);

	char *file_path = malloc(strlen(home_dir) + strlen(HIST_FILE) + 2);

	if (!file_path)
	{
		free(home_dir);
		return (NULL);
	}

	strcpy(file_path, home_dir);
	strcat(file_path, "/");
	strcat(file_path, HIST_FILE);

	free(home_dir);
	return (file_path);
}

/**
 * write_history_to_file - Writes the command history to a file.
 * @info: Parameter struct for shell information.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history_to_file(info_t *info)
{
	int fd;
	char *file_path = get_history_filepath(info);

	if (!file_path)
		return (-1);

	fd = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_path);

	if (fd == -1)
		return (-1);

	list_t *node = info->history;

	if (node)
	{
		do {
			write(fd, node->str, strlen(node->str));
			write(fd, "\n", 1);
			node = node->next;
		} while (node);
	}

	close(fd);
	return (1);
}

/**
 * read_history_from_file - Reads command history from a file.
 * @info: Parameter struct for shell information.
 *
 * Return: Number of history entries read, or 0 on failure.
 */
int read_history_from_file(info_t *info)
{
	int last = 0, linecount = 0, i;
	ssize_t fd, rdlen;
	struct stat st;
	char *buf = NULL;
	char *file_path = get_history_filepath(info);

	if (!file_path)
		return (0);
	fd = open(file_path, O_RDONLY);
	free(file_path);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		if (st.st_size < 2)
			close(fd);
			return (0);
	buf = malloc(st.st_size + 1);
	if (!buf)
		close(fd);
		return (0);
	rdlen = read(fd, buf, st.st_size);
	buf[st.st_size] = '\0';
	if (rdlen <= 0)
		free(buf);
		close(fd);
		return (0);
	close(fd);
	for (i = 0; i < st.st_size; i++)
		if (buf[i] == '\n')
			buf[i] = '\0';
			add_history_entry(info, buf + last, linecount++);
			last = i + 1;
	if (last != st.st_size)
		add_history_entry(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * add_history_entry - Adds an entry to the history linked list.
 * @info: Parameter struct for shell information.
 * @entry: The history entry to add.
 * @linecount: The history line count.
 *
 * Return: Always 0.
 */
int add_history_entry(info_t *info, char *entry, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, entry, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history_entries - Updates the history linked list after changes.
 * @info: Parameter struct for shell information.
 *
 * Return: The new history count.
 */
int renumber_history_entries(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	if (node)
	{
		do {
			node->num = i++;
			node = node->next;
		} while (node);
	}

	return (info->histcount = i);
}
