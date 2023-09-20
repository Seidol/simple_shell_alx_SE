#include "shell.h"

/**
 * _strcpy - Copies a string from source to destination.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 * @n: Maximum number of characters to copy.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src, size_t n)
{
	if (dest == src || src == NULL)
		return (dest);

	for (size_t i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[n - 1] = '\0';

	return (dest);
}

/**
 * _strdup - Duplicates a given string.
 * @str: Pointer to the string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (str[length++])
		;

	ret = malloc(sizeof(char) * (length));
	if (!ret)
		return (NULL);

	for (int i = 0; i < length; i++)
	{
		ret[i] = str[i];
	}

	return (ret);
}

/**
 * _puts - Prints a string to standard output.
 * @str: Pointer to the string to be printed.
 *
 * Return: None.
 */
void _puts(char *str)
{
	if (!str)
		return;

	for (int i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}

/**
 * _putchar - Writes a character to standard output.
 * @c: The character to print.
 *
 * Return: On success, returns 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
