#include "shell.h"

/**
 * _eputs - Displays a given input string
 * @s: The string to be printed
 *
 * This function is responsible for printing
 * the specified string to the output.
 *
 * Return: None
 */

void _eputs(char *s)
{
	int a = 0;

	if (!s)
		return;
	while (s[a] != '\0')
	{
		_eputchar(s[a]);
		a++;
	}
}

/**
 * _eputchar - Outputs the character 'c' to the standard error stream (stderr)
 * @b: The character to be printed
 *
 * This function writes the specified character to
 * the standard error output.
 *
 * Return: Returns 1 on successful execution. On error,
 * it returns -1, and sets the 'errno' appropriately.
 */

int _eputchar(char b)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (b != BUF_FLUSH)
		buf[a++] = b;
	return (1);
}

/**
 * _putfd - Writes the character 'c' to the specified file descriptor 'fd'
 * @c: The character to be printed
 * @fd: The file descriptor to write to
 *
 * This function sends the specified character to the specified file descriptor
 *
 * Return: Returns 1 on successful execution. On error,
 * it returns -1 and sets 'errno' appropriately.
 */

int _putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putsfd - Outputs the specified string to the given file descriptor
 * @s: The string to be printed
 * @fd: The file descriptor to write to
 *
 * This function sends the provided string to the specified file descriptor.
 *
 * Return: Returns the number of characters successfully written.
 */

int _putsfd(char *s, int fd)
{
	int chars_written = 0;

	if (!s)
		return (0);
	while (*s)
	{
		chars_written += _putfd(*s++, fd);
	}
	return (chars_written);
}
