#include "shell.h"

/**
 * _myhistory - Displays the history list, one command per line,
 *                  preceded with line numbers starting at 0.
 * @i: Structure containing potential arguments
 *
 * Return: Always 0
 */
int _myhistory(info_t *i)
{
	print_list(i->history);
	return (0);
}

/**
 * unset_alias - Removes an alias from the alias list
 * @i: Structure containing potential arguments
 * @s: The alias to remove
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *i, char *s)
{
	char *equalSign, originalChar;
	int result;

	equalSign = _strchr(s, '=');
	if (!equalSign)
		return (1);
	originalChar = *equalSign;
	*equalSign = 0;
	result = delete_node_at_index(&(i->alias),
		get_node_index(i->alias, node_starts_with(i->alias, s, -1)));
	*equalSign = originalChar;
	return (result);
}

/**
 * set_alias - Adds or updates an alias in the alias list
 * @info: Structure containing potential arguments
 * @al: The alias to add or update
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *al)
{
	char *equalSign;

	equalSign = _strchr(al, '=');
	if (!equalSign)
		return (1);
	if (!*++equalSign)
		return (unset_alias(info, al));

	unset_alias(info, al);
	return (add_node_end(&(info->alias), al, 0) == NULL);
}

/**
 * print_alias - Displays the information of an alias node
 * @n: Pointer to the alias node containing the information
 *
 * This function is responsible for printing the details of a given alias node,
 * allowing easy visualization of its contents.
 *
 * Return: 0 on successful execution, 1 on error.
 */

int print_alias(list_t *n)
{
	char *equalSign = NULL, *a = NULL;

	if (n)
	{
		equalSign = _strchr(n->str, '=');
		for (a = n->str; a <= equalSign; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(equalSign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Implements functionality similar to the
 * 'alias' built-in command (refer to 'man alias')
 * @info: Pointer to a structure containing potential arguments.
 * This is used to maintain a consistent function prototype.
 *
 * This function emulates the behavior of the 'alias' built-in command.
 * It allows the user to define and view aliases for other commands.
 *
 * Return: Always returns 0 upon successful execution.
 */

int _myalias(info_t *info)
{
	int a = 0;
	char *equalSign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		equalSign = _strchr(info->argv[a], '=');
		if (equalSign)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
