#include "shell.h"

/**
 * input_buf - Buffers chained commands for processing
 * @shell_info: Pointer to the parameter struct for the shell
 * @buf: Address of the buffer storing the input
 * @length: Address of the variable storing the length of the input
 *
 * This function is responsible for managing and buffering chained
 * commands for processing. It takes the parameter struct of the
 * shell, the address of the input buffer, and the address of
 * the length variable. It returns the number of bytes read.
 *
 * Return: Returns the number of bytes read.
 */

ssize_t input_buf(info_t *shell_info, char **buf, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytesRead = getline(buf, &len_p, stdin);
#else
		bytesRead = _getline(shell_info, buf, &len_p);
#endif
		if (bytesRead > 0)
		{
			if ((*buf)[bytesRead - 1] == '\n')
			{
				(*buf)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			shell_info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(shell_info, *buf, shell_info->histcount++);
			{
				*length = bytesRead;
				shell_info->cmd_buf = buf;
			}
		}
	}
	return (bytesRead);
}

/**
 * get_input - Retrieves a line of input excluding the newline character
 * @shell_info: Pointer to the parameter struct
 *
 * This function is responsible for obtaining a line of input,
 * excluding the newline character. It takes the parameter struct
 * as an argument and returns the number of bytes read.
 *
 * Return: Returns the number of bytes read.
 */

ssize_t get_input(info_t *shell_info)
{
	static char *buf;
	static size_t i, j, length;
	ssize_t bytesRead = 0;
	char **buf_p = &(shell_info->arg), *p;

	_putchar(BUF_FLUSH);
	bytesRead = input_buf(shell_info, &buf, &length);
	if (bytesRead == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buf + i;

		check_chain(shell_info, buf, &j, i, length);
		while (j < length)
		{
			if (is_chain(shell_info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			shell_info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (bytesRead);
}

/**
 * read_buf - Reads data into a buffer
 * @info: Pointer to the parameter struct
 * @buf: Buffer to store the read data
 * @i: Size of the buffer
 *
 * This function reads data into the provided buffer
 * using the given size parameter. It returns the number of bytes read.
 *
 * Return: Returns the number of bytes read.
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return (0);
	bytesRead = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*i = bytesRead;
	return (bytesRead);
}

/**
 * _getline - Retrieves the next line of input from standard input (STDIN)
 * @info: Pointer to the parameter struct
 * @ptr: Address of a pointer to a buffer, which can be preallocated or NULL
 * @length: Size of the preallocated buffer (if ptr is not NULL)
 *
 * This function reads the next line of input from standard input (STDIN)
 * using the provided parameter struct. If ptr is not NULL, it uses
 * the preallocated buffer with the specified size.
 * It returns the resulting string.
 *
 * Return: Returns the resulting string.
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytesRead = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	bytesRead = read_buf(info, buf, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - This function handles the SIGINT signal (Ctrl+C).
 *
 * @sig_num: The signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
