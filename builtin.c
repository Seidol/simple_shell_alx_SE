#include "shell.h"

/**
 * shellExit - Exits the shell
 * @info: Structure containing potential arguments
 *
 * Return: Exits with a given exit status
 */
int shellExit(info_t *info)
{
	int exitStatus = 0;

	if (info->argv[1] != NULL)
	{
		exitStatus = _erratoi(info->argv[1]);

		if (exitStatus == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		info->err_num = exitStatus;
	}

	info->err_num = -1;
	return (-2);
}

/**
 * shellChangeDirectory - Changes the current directory of the process
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int shellChangeDirectory(info_t *info)
{
	char *dir, buffer[1024];
	char *currentDir = getcwd(buffer, 1024);

	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (info->argv[1] == NULL)
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = (_getenv(info, "PWD=")) ? _getenv(info, "PWD=") : "/";
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
	}
	else
	{
		dir = info->argv[1];
	}

	if (chdir(dir) == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * shellHelp - Provides help information for the shell
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int shellHelp(info_t *info)
{
	(void)info; /* Unused parameter */

	_puts("Help call works. Function not yet implemented.\n");
	return (0);
}
