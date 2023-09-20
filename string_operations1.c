#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * This function copies the contents of
 * the source string 'src' to the destination
 * buffer 'dest'. It ensures that 'dest' is null-terminated.
 * It returns a pointer to the destination buffer.
 *
 * Return: Pointer to the destination buffer.
 */

char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to be duplicated.
 *
 * This function create nw copy of the input string str allocates memory for it
 * and returns a pointer to the duplicated string.
 *
 * Return: Pointer to the duplicated string, or NULL if memory allocation fails
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--str;
	return (r);
}

/**
 * _puts - Prints a string to the standard output.
 * @str: The string to be printed.
 *
 * This function outputs the characters of
 * the input string 'str' to the standard output.
 * It does not append a newline character.
 *
 * Return: None.
 */

void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - Writes a character to the standard output.
 * @c: The character to be printed.
 *
 * This function writes the specified character 'c' to the standard output.
 * It returns 1 on successful execution. If an error occurs, it returns -1 and
 * sets the 'errno' variable appropriately.
 *
 * Return: 1
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
