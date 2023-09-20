#include "shell.h"

/**
 * getCommandChain - This function reads a line of input,
 * potentially containing
 * chained commands, and stores it in the provided buffer.
 *
 * @shell_info: Parameter struct for shell information
 * @buffer: Address of the buffer to store the input
 * @length: Address of the length variable
 *
 * Return: Number of bytes read
 */
ssize_t getCommandChain(info_t *shell_info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t currentLength = 0;

	/** If there is no remaining data in the buffer, read a new line */
	if (!*length)
	{
		/** Free existing buffer */
		free(*buffer);
		*buffer = NULL;

		/** Set up a signal handler for SIGINT (Ctrl+C) */
		signal(SIGINT, handleSIGINT);

		/** Read a line from standard input */
		#if USE_GETLINE
			bytesRead = getline(buffer, &currentLength, stdin);
		#else
			bytesRead = customGetLine(shell_info, buffer,
			&currentLength);
		#endif

		/** Process the input if read was successful */
		if (bytesRead > 0)
			/** Remove trailing newline character */
			if ((*buffer)[bytesRead - 1] == '\n')
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			/** Update shell information */
			shell_info->linecount_flag = 1;
			remove_comments(*buffer);
			add_history_entry(shell_info, *buffer,
			shell_info->histcount++);

			/** Update length and command buffer in shell_info */
			*length = bytesRead;
			shell_info->cmd_buf = buffer;
	}

	return (bytesRead);
}

/**
 * processInput - This function processes the input, potentially containing
 * multiple chained commands.
 *
 * @shell_info: Parameter struct for shell information
 *
 * Return: Number of bytes read
 */
ssize_t processInput(info_t *shell_info)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t bytesRead = 0;
	char **arg_p = &(shell_info->arg), *p;

	/** Flush the buffer */
	_putchar(BUF_FLUSH);

	/** Read a line, potentially with chained commands */
	bytesRead = getCommandChain(shell_info, &buffer, &length);

	/** If end of input is reached, return -1 (EOF) */
	if (bytesRead == -1)
		return (-1);

	/** If there are commands in the buffer */
	if (length)
	{
		j = i;
		p = buffer + i;
		getCommandChain(shell_info, &buffer, &j);
		for (; j < length; j++)
			if (getCommandChain(shell_info, &buffer, &j))
				break;

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			shell_info->cmd_buf_type = CMD_NORM;
		}

		*arg_p = p; /** Set the current command pointer */
		return (_strlen(p)); /** Return the length of current command */
	}

	*arg_p = buffer; /** If no chained command, return the buffer */
	return (bytesRead); /** Return the total bytes read */
}

/**
 * readBuffer - This function reads data into a buffer.
 *
 * @shell_info: Parameter struct for shell information
 * @buf: Buffer to read data into
 * @i: Size of data
 *
 * Return: Number of bytes read
 */
ssize_t readBuffer(info_t *shell_info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;

	/** If there's data in the buffer, return 0 (no additional read) */
	if (*i)
		return  (0);

	/** Read data from file descriptor into buffer */
	bytesRead = read(shell_info->readfd, buf, READ_BUF_SIZE);

	/** Update size 'i' with number of bytes read */
	if (bytesRead >= 0)
		*i = bytesRead;

	return (bytesRead);
}

/**
 * customGetLine - This function get the nxt line of input from standard input.
 *
 * @shell_info: Parameter struct for shell information
 * @ptr: Address of pointer to buffer (preallocated or NULL)
 * @length: Size of preallocated buffer if not NULL
 *
 * Return: Number of bytes read
 */
int customGetLine(info_t *shell_info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytesRead = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		bytesRead = *length;
	if (i == len)
		i = len = 0;
	bytesRead = readBuffer(shell_info, buf, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return (-1);
	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, bytesRead, bytesRead ? bytesRead + k : k + 1);
	if (!new_p)
		return (p ? (free(p), -1) : -1);
	if (bytesRead)
		_strcat(new_p, buf + i, k - i);
	else
		_strcpy(new_p, buf + i, k - i + 1);
	bytesRead += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = bytesRead;
	*ptr = p; /** Update buffer pointer */
	return (bytesRead); /** Return total bytes read */
}

/**
 * handleSIGINT - This function handles the SIGINT signal (Ctrl+C).
 *
 * @sig_num: The signal number
 *
 * Return: void
 */
void handleSIGINT(__attribute__((unused)) int sig_num)
{
	/** Print newline and shell prompt */
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
