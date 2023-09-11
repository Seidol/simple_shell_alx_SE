#include "shell.h"

/**
 * isInteractive - checks if the shell is in interactive mode
 * @info: pointer to struct containing shell information
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int isInteractive(info_t *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return (1);
	else
		return (0);
}

/**
 * isDelimiter - checks if a character is a delimiter
 * @character: the character to check
 * @delimiterString: string containing delimiters
 *
 * Return: 1 if character is a delimiter, 0 otherwise
 */
int isDelimiter(char character, char *delimiterString)
{
	while (*delimiterString)
	{
		if (*delimiterString == character)
			return (1);
		delimiterString++;
	}
	return (0);
}

/**
 * isAlphabetic - checks if a character is alphabetic
 * @character: the character to check
 *
 * Return: 1 if character is alphabetic, 0 otherwise
 */
int isAlphabetic(int character)
{
	if ((character >= 'a' && character <= 'z') ||
		(character >= 'A' && character <= 'Z'))
		return (1);
	return (0);
}

/**
 * customAtoi - converts a string to an integer
 * @string: the string to convert
 *
 * Return: the converted integer, or 0 if no numbers are found in the string
 */
int customAtoi(char *string)
{
	int i = 0, sign = 1, flag = 0, result = 0;

	while (string[i] != '\0' && flag != 2)
	{
		if (string[i] == '-')
			sign *= -1;

		if (string[i] >= '0' && string[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (string[i] - '0');
		}
		else if (flag == 1)
			flag = 2;

		i++;
	}

	return (sign * result);
}
