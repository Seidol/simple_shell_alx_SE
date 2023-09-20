#include "shell.h"

/**
 * convert_string_to_integer - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: The converted integer, or -1 if conversion fails
 */
int convert_string_to_integer(char *str)
{
	int i = 0;
	unsigned long int r = 0;

	if (*str == '+')
		str++;

	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			r *= 10;
			r += (str[i] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (r);
}

/**
 * print_custom_error - prints a custom error message
 * @info: information about the command
 * @error_type: string containing the specified error type
 */
void print_custom_error(info_t *info, char *error_type)
{
	custom_puts(info->fname);
	custom_puts(": ");
	print_custom_integer(info->line_count, STDERR_FILENO);
	custom_puts(": ");
	custom_puts(info->argv[0]);
	custom_puts(": ");
	custom_puts(error_type);
}

/**
 * print_custom_integer - prints a custom integer to a file descriptor
 * @input: the integer to print
 * @fd: the file descriptor to write to
 * Return: none
 */
int print_custom_integer(int input, int fd)
{
	int (*put_char)(char) = custom_putchar;
	int count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		put_char = custom_putchar;

	if (input < 0)
	{
		absolute = -input;
		put_char('-');
		count++;
	}
	else
		absolute = input;
	current = absolute;

	int divisor = 1000000000;

	while (divisor > 1)
	{
		if (absolute / divisor)
		{
			put_char('0' + current / divisor);
			count++;
		}
		current %= divisor;
		divisor /= 10;
	}

	put_char('0' + current);
	count++;
}

/**
 * convert_number_to_string - converts a number to a string
 * @num: number to convert
 * @base: base for conversion
 * @flags: flags for conversion
 *
 * Return: The converted string
 */
char *convert_number_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 */
void remove_comments(char *buffer)
{
	int i = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}
}
