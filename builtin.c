#include "shell.h"

/**
 * _myexit - Exits the shell
 * @i: Structure containing potential arguments
 *
 * Return: Exits with a given exit status
 */
int _myexit(info_t *i)
{
	int exitcheck;

	if (i->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(i->argv[1]);
		if (exitcheck == -1)
		{
			i->status = 2;
			print_error(i, "Illegal number: ");
			_eputs(i->argv[1]);
			_eputchar('\n');
			return (1);
		}
		i->err_num = _erratoi(i->argv[1]);
		return (-2);
	}
	i->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes the current directory of the process
 * @i: Structure containing potential arguments
 *
 * Return: Always 0
 */
int _mycd(info_t *i)
{
	char *s, *d, buffer[1024];
	int c;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!i->argv[1])
	{
		d = _getenv(i, "HOME=");
		if (!d)
			c =
				chdir((d = _getenv(i, "PWD=")) ? d : "/");
		else
			c = chdir(d);
	}
	else if (_strcmp(i->argv[1], "-") == 0)
	{
		if (!_getenv(i, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(i, "OLDPWD=")), _putchar('\n');

		c = chdir((d = _getenv(i, "OLDPWD=")) ? d : "/");
	}
	else
		c = chdir(i->argv[1]);
	if (c == -1)
	{
		print_error(i, "can not cd to ");
		_eputs(i->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(i, "OLDPWD", _getenv(i, "PWD="));
		_setenv(i, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Provides help information for the shell
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
