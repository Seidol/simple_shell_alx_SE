#include "shell.h"

/**
 * _erratoi - Converts a string to an integer
 * @s: The string to be converted
 *
 * This function attempts to convert the provided string
 * to an integer. If the string contains no numbers, it returns 0.
 * If an error occurs during the conversion process, it returns -1.
 *
 * Return: The converted integer if successful,
 * 0 if no numbers are found in the string, or -1 on error.
 */

int _erratoi(char *s)
{
	int a = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			r *= 10;
			r += (s[a] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * print_error - Displays an error message
 * @info: Pointer to the parameter and return info struct
 * @estr: String containing the specified error type
 *
 * This function is responsible for printing out an error message.
 * It takes a pointer to the parameter and return info struct,
 * as well as a string indicating the type of error.
 *
 * Return: Returns 0 if no numbers are found in the string,
 * otherwise returns -1 on error.
 */

void print_error(info_t *i, char *error_type)
{
	_eputs(i->fname);
	_eputs(": ");
	print_d(i->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(i->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_d - This function prints a decimal (base 10) integer.
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function takes an integer input and writes it
 * to the specified file descriptor in decimal format (base 10).
 * It returns the number of characters printed.
 *
 * Return: The number of characters printed.
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, c = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		absolute = -input;
		__putchar('-');
		c++;
	}
	else
		absolute = input;
	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			__putchar('0' + current / i);
			c++;
		}
		current %= i;
	}
	__putchar('0' + current);
	c++;

	return (c);
}

/**
 * convert_number - Conversion function similar to 'itoa'
 * @num: The number to be converted
 * @base: The base for conversion
 * @flags: Flags for conversion
 *
 * This function converts the given number into a string representation
 * based on the specified base. The resulting string is returned.
 *
 * Return: A string representing the converted number.
 */

char *convert_number(long int nu, int b, int f)
{
	static char *arr;
	static char buffer[50];
	char sn = 0;
	char *ptr;
	unsigned long n = nu;

	if (!(f & CONVERT_UNSIGNED) && n < 0)
	{
		n = -nu;
		sn = '-';

	}
	arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sn)
		*--ptr = sn;
	return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0'
 * @buf: The address of the string to modify
 *
 * This function is responsible for locating the first occurrence
 * of '#' in the string and replacing it with the null character
 * '\0'. It operates on the string at the provided address.
 *
 * Return: Always returns 0.
 */

void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
