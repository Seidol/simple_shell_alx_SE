#include "shell.h"

/**
 * get_environ - Retrieves a copy of the string array
 * containing our environment variables
 * @info: Pointer to a structure containing potential arguments.
 * This is used to maintain a consistent function prototype.
 *
 * This function returns a copy of the string array containing
 * our environment variables. It provides a snapshot of
 * the system's configuration.
 *
 * Return: Always returns 0.
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes an environment variable
 * @info: Pointer to a structure containing potential arguments. This is used
 * to maintain a consistent function prototype.
 * @var: The string representing the environment variable to be removed
 *
 * This function is responsible for deleting an environment variable.
 * It takes a pointer to the parameter struct and the name of the environment
 * variable to be removed. It returns 1 upon successful deletion,
 * and 0 otherwise.
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	for (size_t i = 0; node; node = node->next, i++)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
		}
	}
	return (info->env_changed);
}

/**
 * _setenv - Initializes a new environment variable or modifies an existing one
 * @info: Pointer to a structure containing potential arguments.
 * This is used to maintain a consistent function prototype.
 * @var: The string representing the environment variable property
 * @value: The string representing the value of the environment variable
 *
 * This function is responsible for creating a new environment
 * variable or modifying an existing one. It takes a pointer to
 * the parameter struct, the name of the environment variable,
 * and its value. It always returns 0.
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	for (node = info->env; node; node = node->next)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
