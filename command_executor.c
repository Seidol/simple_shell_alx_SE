#include "shell.h"

/**
 * is_executable - Checks if a file is an executable command.
 * @info: Pointer to the info struct.
 * @filepath: The path to the file.
 *
 * Returns: 1 if it's an executable, 0 otherwise.
 */
int is_executable(info_t *info, char *filepath)
{
	struct stat file_stat;

	(void)info;

	if (!filepath || stat(filepath, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * extract_chars - Extracts characters from a string.
 * @source: The source string.
 * @start: Starting index.
 * @end: Ending index.
 *
 * Returns: A pointer to the newly created buffer.
 */
char *extract_chars(char *source, int start, int end)
{
	static char buffer[1024];
	int k = 0;

	do {
		if (source[start] != ':')
			buffer[k++] = source[start];
		start++;
	} while (start < end);

	buffer[k] = '\0';
	return (buffer);
}

/**
 * find_command_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to the info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Returns: Full path of the command if found, otherwise NULL.
 */
char *find_command_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}

	do {
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = extract_chars(pathstr, curr_pos, i);

			if (!*path)
				_strcat(path, cmd, sizeof(path) - strlen(path) - 1);
			else
			{
				_strcat(path, "/",
					sizeof(path) - strlen(path) - 1);
				_strcat(path, cmd,
					sizeof(path) - strlen(path) - 1);
			}

			if (is_executable(info, path))
				return (path);

			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	} while (1);

	return (NULL);
}
