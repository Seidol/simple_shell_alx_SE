#include "shell.h"

/**
 * _strncpy - Copies a string from source to destination
 * @destination: The destination string where the copy will be placed
 * @source: The source string to be copied
 * @max_chars: The maximum number of characters to copy
 *
 * This function performs a string copy operation from
 * 'src' to 'dest'. It copies up to 'n' characters and
 * returns the concatenated string.
 *
 * Return: Returns the resulting concatenated string.
 */

char *_strncpy(char *destination, char *source, int max_chars)
{
	int i, j;
	char *start = destination;

	i = 0;
	while (source[i] != '\0' && i < max_chars - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < max_chars)
	{
		j = i;
		while (j < max_chars)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (start);
}

/**
 * _strncat - Concatenates two strings
 * @destination: The first string (destination)
 * @source: The second string (source)
 * @max_chars: The maximum number of bytes to be used from 'src'
 *
 * This function concatenates the 'n' most significant bytes from
 * 'src' to the end of 'dest'. It returns the resulting concatenated string.
 *
 * Return: Returns the resulting concatenated string.
 */

char *_strncat(char *destination, char *source, int max_chars)
{
	int i, j;
	char *start = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < max_chars)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < max_chars)
		destination[i] = '\0';
	return (start);
}

/**
 * _strchr - Locates a character in a string
 * @s: The string to be searched
 * @c: The character to look for
 *
 * This function searches for the first occurrence of the characte
 * 'c' in the string 's'. If found, it returns a pointer to the memory
 * area where 'c' is located; otherwise, it returns NULL.
 *
 * Return: Returns a pointer to the memory area containing
 * the character 'c' if found in the string 's'.
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
