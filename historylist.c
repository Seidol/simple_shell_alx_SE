#include "shell.h"

/**
 * displayHistory - Displays the history list, one command per line,
 *                  preceded with line numbers starting at 0.
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int displayHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * removeAlias - Removes an alias from the alias list
 * @info: Structure containing potential arguments
 * @alias: The alias to remove
 *
 * Return: Always 0 on success, 1 on error
 */
int removeAlias(info_t *info, char *alias)
{
	char *equalSign, originalChar;
	int result;

	equalSign = strchr(alias, '=');
	if (!equalSign)
		return (1);

	originalChar = *equalSign;
	*equalSign = 0;

	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, find_node_with_prefix(info->alias, alias, -1)));

	*equalSign = originalChar;
	return (result);
}

/**
 * addAlias - Adds or updates an alias in the alias list
 * @info: Structure containing potential arguments
 * @alias: The alias to add or update
 *
 * Return: Always 0 on success, 1 on error
 */
int addAlias(info_t *info, char *alias)
{
	char *equalSign, *value;

	equalSign = strchr(alias, '=');
	if (!equalSign || !*(equalSign + 1))
		return (1);

	*equalSign = 0;
	value = equalSign + 1;

	removeAlias(info, alias);
	return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * printAlias - Prints an alias string
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
	char *equalSign, *name;

	if (node)
	{
		equalSign = strchr(node->str, '=');
		if (!equalSign)
			return (1);

		name = node->str;

		while (name < equalSign)
			_putchar(*name++);

		_puts("'");
		_puts(equalSign + 1);
		_puts("'\n");

		return (0);
	}

	return (1);
}

/**
 * aliasCommand - Mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
int aliasCommand(info_t *info)
{
	int i;
	char *equalSign;

	if (info->argc == 1)
	{
		list_t *node = info->alias;

		while (node)
		{
			printAlias(node);
			node = node->next;
		}

		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equalSign = strchr(info->argv[i], '=');

		if (equalSign)
			addAlias(info, info->argv[i]);
		else
			printAlias(find_node_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}
