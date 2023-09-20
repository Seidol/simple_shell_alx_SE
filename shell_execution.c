#include "shell.h"

/**
 * hsh - Main shell loop that handles command execution and user interaction.
 * @info: Structure containing potential arguments
 * and return information.
 * @av: Argument vector from the main() function.
 *
 * Return: 0 on success, 1 on error, or an error code.
 *
 * This function serves as the primary loop for the shell,
 * responsible for executing commands
 * and interacting with the user. It takes in a structure
 * with relevant information and an argument
 * vector from the main program. It returns various codes
 * to indicate the status of execution.
 */

int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtinret = 0;

	while (r != -1 && builtinret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtinret = find_builtin(info);
			if (builtinret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtinret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtinret);
}

/**
 * find_builtin - Finds and handles a built-in command.
 * @info: Structure containing potential arguments and return information.
 *
 * Return: -1 if built-in not found,
 * 0 if built-in executed successfully,
 * 1 if built-in found but not successful,
 * -2 if built-in signals exit()
 *
 * This function is responsible for locating and
 * processing built-in commands. It takes in a
 * structure with relevant information and returns
 * codes to indicate the outcome of the operation.
 */

int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Searches for a command in the PATH environment variable.
 * @info: Structure containing potential arguments and
 * return information.
 *
 * This function is responsible for locating a command
 * in the PATH directories. It takes in a
 * structure with relevant information and performs
 * the necessary actions to find the command.
 * Return: none
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Creates a child process to execute a command.
 * @info: Structure containing potential arguments and return information.
 *
 * This function is responsible for creating
 * a new process to run a command. It takes in a
 * structure with relevant information and performs
 * the necessary actions to execute the command.
 *
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
