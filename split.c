#include "shell.h"

/**
 * strtow - Splits a string into words, ignoring repeated delimiters.
 * @str: The input string.
 * @d: The delimiter string.
 *
 * This function takes an input string 'str' and a delimiter string 'd' to
 * split 'str' into individual words. It returns a pointer to an array of
 * strings containing the words. If an error occurs, it returns NULL.
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int a, b, c, u = 0, nwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (u = 0; u < b; u++)
				free(s[u]);
			free(s);
			return (NULL);
		}
		for (u = 0; u < c; u++)
			s[b][u] = str[a++];
		s[b][u] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * strtow2 - Splits a string into words using a specified delimiter.
 * @str: The input string to be split.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **strtow2(char *str, char d)
{
	int i, j, k, m = 0, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (m = 0; m < j; m++)
				free(s[m]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
