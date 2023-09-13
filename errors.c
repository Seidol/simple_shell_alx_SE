#include "shell.h"

/**
 * custom_puts - Prints a custom string to standard error.
 * @custom_str: The string to be printed.
 *
 * This function prints the characters of the custom string to the standard
 * error output.
 * If the input string is NULL, it does nothing.
 */
void custom_puts(char *custom_str)
{
	int custom_index = 0;

	if (!custom_str)
		return;

	do {
		custom_putchar(custom_str[custom_index]);
		custom_index++;
	} while (custom_str[custom_index] != '\0');
}

/**
 * custom_putchar - Writes a character to standard error.
 * @c: The character to print.
 *
 * This function writes the specified character to the standard error output.
 * If the character is a special value for flushing the buffer or the buffer
 * is full,
 * it flushes the buffer to the standard error output.
 */
int custom_putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
		return (1);
}

/**
 * custom_putfd - Writes a character to a given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * This function writes the specified character to the given file descriptor.
 * If the character is a special value for flushing the buffer or the buffer
 * is full,
 * it flushes the buffer to the specified file descriptor.
 */
int custom_putfd(char c, int fd)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
		return (1);
}

/**
 * custom_putsfd - Prints a custom string to a given file descriptor.
 * @custom_str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function prints the characters of the custom string to the
 * specified file descriptor.
 * If the input string is NULL, it does nothing.
 */
int custom_putsfd(char *custom_str, int fd)
{
	int custom_index = 0;
	int chars_written = 0;

	if (!custom_str)
		return (0);

	do {
		chars_written += custom_putfd(custom_str[custom_index], fd);
		custom_index++;
	} while (custom_str[custom_index] != '\0');

	return (chars_written);
}
