#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: The string whose length is to be determined.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	int a;

	if (!s)
		return (0);

	for (a = 0; *s; s++)
		a++;

	return (a);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int _strcmp(char *s1, char *s2)
{
	for (; *s1 && *s2; s1++, s2++)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if 'needle' starts with 'haystack'.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of 'haystack' or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	for (; *needle; needle++, haystack++)
	{
		if (*needle != *haystack)
			return (NULL);
	}

	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src, size_t n)
{
	char *r = dest;

	for (; *dest; dest++)
		;

	for (; *src && n > 0; src++, n--)
		*dest = *src;

	*dest = '\0';
	return (r);
}

