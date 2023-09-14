#include "shell.h"

/**
 * custom_str_copy - Copies a string.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @max_chars: The maximum number of characters to be copied.
 *
 * Return: The pointer to the start of the destination string.
 */
char *custom_str_copy(char *destination, const char *source, int max_chars)
{
	char *start = destination;
	int i;

	for (i = 0; i < max_chars - 1 && *source != '\0'; i++)
	{
		*destination = *source;
		destination++;
		source++;
	}

	if (i < max_chars)
	{
		for (; i < max_chars; i++)
			*destination++ = '\0';
	}

	return (start);
}

/**
 * custom_str_concat - Concatenates two strings.
 * @destination: The first string.
 * @source: The second string.
 * @max_chars: The maximum number of characters to be used.
 *
 * Return: The pointer to the start of the concatenated string.
 */
char *custom_str_concat(char *destination, const char *source, int max_chars)
{
	char *start = destination;

	while (*destination != '\0')
		destination++;

	int i;

	for (i = 0; i < max_chars && *source != '\0'; i++)
	{
		*destination = *source;
		destination++;
		source++;
	}

	if (i < max_chars)
		*destination = '\0';

	return (start);
}

/**
 * custom_str_find_char - Locates a character in a string.
 * @str: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area in 'str'.
 */
char *custom_str_find_char(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
