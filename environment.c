#include "shell.h"

/**
 *	displayEnvironment - Prints the current environment variables.
 *	@info: Structure containing potential arguments and environment data.
 *
 *	This function prints the list of environment variables.
 *
 *	Return: Always 0.
 */
int displayEnvironment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 *	getEnvironmentVariable - Retrieves the value of an environment variable.
 *	@info: Structure containing potential arguments and environment data.
 *	@name: Name of the environment variable.
 *
 *	This function searches for the specified environment variable and
 *	returns its value.
 *
 *	Return: The value of the environment variable or NULL if not found.
 */
char *getEnvironmentVariable(info_t *info, const char *name)
{
	list_t *n = info->env;
	char *p;

	while (n)
	{
		p = starts_with(n->str, name);
		if (p && *p)
			return (p);
		n = n->next;
	}

	return (NULL);
}

/**
 *	setEnvironmentVariable - Initializes or modifies an environment variable.
 *	@info: Structure containing potential arguments and environment data.
 *
 *	This function sets or modifies an environment variable with the
 *	specified value.
 *	If the variable already exists, it updates its value; otherwise,
 *	it creates a
 *	new environment variable.
 *
 *	Return: Always 0.
 */
int setEnvironmentVariable(info_t *info)
{
	if (info->argc != 3)
	{
		_puts("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 *	unsetEnvironmentVariable - Removes an environment variable.
 *	@info: Structure containing potential arguments and environment data.
 *
 *	This function removes the specified environment variable.
 *
 *	Return: Always 0.
 */
int unsetEnvironmentVariable(info_t *info)
{
	int a = 1;

	if (info->argc == 1)
	{
		_puts("Too few arguments.\n");
		return (1);
	}

	while (info->argv[a])
	{
		_unsetenv(info, info->argv[a]);
		a++;
	}

	return (0);
}

/**
 *	populateEnvironmentList - Populates the environment linked list.
 *	@info: Structure containing potential arguments and environment data.
 *
 *	This function fills the linked list with the current environment variables.
 *
 *	Return: Always 0.
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);

	info->env = node;
	return (0);
}
