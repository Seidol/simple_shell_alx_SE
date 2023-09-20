#include "shell.h"

/**
 * hsh - The main loop of the shell program.
 * @info: Pointer to the info struct for parameters and return values.
 * @av: The argument vector from the main function.
 *
 * This function is the central loop of the shell program.It manages user input
 * processes commands, and executes built-in functions or external commands.
 * Return: 0 on success, 1 on error, or an error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	do {
		clear_info(info);

		if (interactive(info))
			_puts("$ ");

		_putchar(BUF_FLUSH);

		read_result = processInput(info);

		if (read_result != -1)
			set_info(info, av);
			builtin_result = find_builtin(info);

			if (builtin_result == -1)
				find_cmd(info);
		else if (interactive(info))
			_putchar('\n');

		free_info(info, 0);

	} while (read_result != -1 && builtin_result != -2);

	read_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}

	return (builtin_result);
}

/**
 * find_builtin - Searches for a built-in command and executes it if found.
 * @info: Pointer to the info struct for parameters and return values.
 *
 * This function looks for a built-in command in the provided info struct.
 * If a matchis found, it executes the corresponding function.
 * Return: -1 if builtin not found, 0 if successful,
 * 1 if found but not successful,
 * -2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
	int i = 0;
	int built_in_result = -1;

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

	do {
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[i].func(info);
			break;
		}
		i++;
	} while (builtintbl[i].type);

	return (built_in_result);
}

/**
 * find_cmd - Attempts to locate and execute a command within the info struct.
 * @info: Pointer to the info struct for parameters and return values.
 *
 * This function tries to find executable cmd within the provided info struct.
 * If found, it proceeds to execute the command.
 * Return: Empty
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i = 0;
	int k = 0;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	do {
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
		i++;
	} while (info->arg[i]);

	if (!k)
		return;

	path = find_command_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") ||
		info->argv[0][0] == '/') && is_executable(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Creates a new process to execute a command.
 * @info: Pointer to the info struct for parameters and return values.
 *
 * This function forks new process and executes a command in the child process.
 * It also waits for the child process to finish in the parent process.
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
