#include "shell.h"

/**
 * is_chain - Checks if the current character in
 * the buffer is a chaining delimiter.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if it's a chaining delimiter, 0 otherwise.
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t h = *p;

	if (buf[h] == '|' && buf[h + 1] == '|')
	{
		buf[h] = 0;
		h++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[h] == '&' && buf[h + 1] == '&')
	{
		buf[h] = 0;
		h++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[h] == ';')
	{
		buf[h] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = h;
	return (1);
}

/**
 * check_chain - Determines whether we should
 * continue chaining based on the last status.
 * @info: The parameter structcure.
 * @buf: The character buffer.
 * @p: Address of the current position in buffer.
 * @i: Starting position in buffer.
 * @len: Length of buffer.
 *
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t h = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			h = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			h = len;
		}
	}

	*p = h;
}

/**
 * replace_alias - Substitutes aliases in the tokenized
 * string with their definitions.
 * @info: The parameter struct containing alias information.
 *
 * Return: Returns 1 if any alias is replaced, otherwise returns 0.
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Performs variable substitution in the tokenized string.
 * @info: The parameter struct containing variable information.
 *
 * Return: Returns 1 if any variable is replaced, otherwise returns 0.
 */

int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces occurrences of a string with a new string.
 * @old: Address of the old string to be replaced.
 * @new: The new string to replace with.
 *
 * Return: Returns 1 if any replacement occurs, otherwise returns 0.
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
