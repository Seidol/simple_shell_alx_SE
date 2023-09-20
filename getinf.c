#include "shell.h"

/**
 * clear_info - Initializes the info_t struct
 * @info: Address of the struct to be initialized
 *
 * This function is responsible for initializing
 * the info_t struct. It takes the address of the
 * struct as an argument and performs the necessary initialization steps.
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes the info_t struct
 * @info: Address of the struct to be initialized
 * @av: Argument vector
 *
 * This function is responsible for initializing
 * the info_t struct. It takes the address of the struct
 * as well as the argument vector (av) and performs
 * the necessary initialization steps.
 */

void set_info(info_t *info, char **av)
{
	int a = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Releases memory associated with fields in the info_t struct
 * @info: Address of the struct containing fields to be freed
 * @all: True if freeing all fields, otherwise only specific fields are freed
 *
 * This function is responsible for freeing the memory associated with fields
 * in the info_t struct. It takes the address of the struct and
 * a flag indicating whether to free all fields or only specific ones.
 */

void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
