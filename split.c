#include "shell.h"

/**
 * **strtow - Splits a string into an array of words,
 * ignoring repeated delimiters.
 * @str: The input string.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int i = 0, j = 0, k = 0, m = 0, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	while (str[i] != '\0')
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;
		i++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (j < numwords)
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
			k = 0;
			while (k < j)
				free(s[k]);
				k++;
			free(s);
			return (NULL);
		m = 0;
		while (m < k)
			s[j][m] = str[i++];
			m++;
		s[j][m] = 0;
		j++;
	s[j] = NULL;
	return (s);
}
/**
 * strtow2 - Splits a string into an array of words using a specified delimiter
 * @str: The input string to be split.
 * @d: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **strtow2(char *str, char d)
{
	int i = 0, j = 0, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	while (str[i] != '\0')
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
		i++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (j < numwords)
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
			k = 0;
			while (k < j)
				free(s[k]);
				k++;
			free(s);
			return (NULL);
		m = 0;
		while (m < k)
			s[j][m] = str[i++];
			m++;
		s[j][m] = 0;
		j++;
	s[j] = NULL;
	return (s);
}
