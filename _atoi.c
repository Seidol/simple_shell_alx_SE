#include "shell.h"

/**
 * interactive - checks if the shell is in interactive mode
 * @i: pointer to struct containing shell information
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(info_t *i)
{
	return (isatty(STDIN_FILENO) && i->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimiter
 * @character: the character to check
 * @delimiterString: string containing delimiters
 *
 * Return: 1 if character is a delimiter, 0 otherwise
 */
int is_delim(char character, char *delimiterString)
{
	while (*delimiterString)
		if (*delimiterString++ == character)
			return (1);
	return (0);
}

/**
 * _isalpha - checks if a character is alphabetic
 * @character: the character to check
 *
 * Return: 1 if character is alphabetic, 0 otherwise
 */

int _isalpha(int character)
{
	if ((character >= 'a' && character <= 'z') ||
	(character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @string: the string to convert
 *
 * Return: the converted integer, or 0 if no numbers are found in the string
 */

int _atoi(char *string)
{
	int a, s = 1, f = 0, output;
	unsigned int r = 0;

	for (a = 0;  string[a] != '\0' && f != 2; a++)
	{
		if (string[a] == '-')
			s *= -1;

		if (string[a] >= '0' && string[a] <= '9')
		{
			f = 1;
			r *= 10;
			r += (string[a] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (s == -1)
		output = -r;
	else
		output = r;

	return (output);
}
