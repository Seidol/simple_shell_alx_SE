#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: Pointer to the string to be measured.
 *
 * This function counts the number of characters
 * in the input string until it reaches the
 * null-terminating character ('\0').
 *
 * Return: The length of the string.
 */

int _strlen(char *s)
{
	int k = 0;

	if (!s)
		return (0);

	while (*s++)
		k++;
	return (k);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @s1: The first string.
 * @s2: The second string.
 *
 * This function compares the characters of
 * both input strings until a difference is found,
 * or until the null-terminating character ('\0') is reached in either string.
 *
 * Return: Returns a negative value if s1 is less than s2,
 * a positive value if s1 is greater
 * than s2, and 0 if both strings are equal.
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if the string 'haystack'
 * starts with the substring 'needle'.
 * @haystack: The string to search.
 * @ndle: The substring to find.
 *
 * This function determines if the string 'haystack'
 * begins with the characters in 'needle'.
 * If a match is found, it returns the address of
 * the next character in 'haystack' after the match.
 * If no match is found, it returns NULL.
 *
 * Return: Address of the next character in 'haystack'
 * after the match, or NULL if no match is found.
 */

char *starts_with(const char *haystack, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * This function append the contents of the source string src to the end of the
 * destination string 'dest'. The resulting string is null-terminated.
 * It returns a pointer to the destination buffer.
 *
 * Return: Pointer to the destination buffer.
 */

char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
