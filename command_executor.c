#include "shell.h"

/**
 * is_cmd - Checks if a file located at the specified path
 * is an executable command.
 * @info: Pointer to the info struct.
 * @path: Path to the file.
 *
 * This function evaluates whether the file at the given path
 * is an executable command.
 * Return: 1 if it is an executable command, 0 otherwise.
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters from the PATH string
 * within the specified range.
 * @pathstr: The original PATH string.
 * @start: Starting index of the range.
 * @stop: Stopping index of the range.
 *
 * This function creates a new buffer and copies characters
 * from the PATH string within the specified range.
 * Return: Pointer to the new buffer.
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; b < stop; a++)
		if (pathstr[a] != ':')
			buf[b++] = pathstr[a];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path - Searches for the specified command in the PATH string.
 * @info: Pointer to the info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * This function looks for the given command within
 * the directories specified in the PATH string.
 * Return: The full path of the command if found, or NULL if not found.
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, cpos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, cpos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			cpos = i;
		}
		i++;
	}
	return (NULL);
}
