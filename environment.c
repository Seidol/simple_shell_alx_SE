#include "shell.h"

/**
 * _myenv - Displays the current environment variables
 * @i: Pointer to a structure containing potential arguments.
 * This is used to maintain a consistent function prototype.
 *
 * This function prints out the current environment variables.
 * It provides a snapshot of the system's configuration.
 *
 * Return: Always returns 0 upon successful execution.
 */

int _myenv(info_t *i)
{
	print_list_str(i->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable
 * @i: Pointer to a structure containing potential arguments.
 * This is used to maintain a consistent function prototype.
 * @n: Name of the environment variable to retrieve
 *
 * This function retrieves the value associated with
 * the specified environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */

char *_getenv(info_t *i, const char *n)
{
	list_t *n = i->env;
	char *p;

	while (n)
	{
		p = starts_with(n->str, n);
		if (p && *p)
			return (p);
		node = n->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Creates a new environment variable or updates an existing one
 * @info: Pointer to a structure containing potential arguments.
 * This is used to maintain a consistent function prototype.
 *
 * This function allows for the creation of a new environment variable
 * or the modification of an existing one.
 * It provides a way to manage the system's configuration.
 *
 * Return: Always returns 0 upon successful execution.
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Invalid number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Deletes an environment variable
 * @info: Pointer to a structure containing potential arguments.
 * This is used to maintain a consistent function prototype.
 *
 * This function allows for the removal of a specific
 * environment variable,effectively deleting it from the system's configuration
 *
 * Return: Always returns 0 upon successful execution.
 */

int _myunsetenv(info_t *info)
{
	int b;

	if (info->argc == 1)
	{
		_eputs("Insufficient number of arguments.\n");
		return (1);
	}
	for (b = 1; b <= info->argc; b++)
		_unsetenv(info, info->argv[b]);

	return (0);
}

/**
 * populate_env_list - Fills a linked list with environment variables
 * @info: Pointer to a structure containing potential arguments.
 * This is used to maintain a consistent function prototype.
 *
 * This function populates a linked list with environment
 * variables, allowing for easy management and access to the
 * system's configuration.
 *
 * Return: Always returns 0 upon successful execution.
 */

int populate_env_list(info_t *info)
{
	list_t *n = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&n, environ[i], 0);
	info->env = n;
	return (0);
}
