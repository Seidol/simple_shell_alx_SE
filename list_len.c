#include "shell.h"

/**
 * list_length - Calculates the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t list_length(const list_t *head)
{
	size_t size = 0;

	for (; head; head = head->next)
		size++;

	return (size);
}

/**
 * list_to_strings - Converts a linked list of strings into
 * an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
	size_t size = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !size)
		return (NULL);

	strs = malloc(sizeof(char *) * (size + 1));
	if (!strs)
		return (NULL);

	for (size_t b = 0; head; head = head->next, b++)
	{
		str = malloc(_strlen(head->str) + 1);
		if (!str)
		{
			for (j = 0; j < b; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, head->str, _strlen(head->str));
		strs[b] = str;
	}

	strs[size] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *head)
{
	size_t size = 0;

	for (; head; head = head->next, size++)
	{
		_puts(convert_number_to_string(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
	}

	return (size);
}

/**
 * find_node_with_prefix - Finds a node with a string starting with a prefix.
 * @head: Pointer to the list head.
 * @prefix: Prefix to match.
 * @c: The next character after the prefix to match.
 *
 * Return: A matching node or NULL.
 */
list_t *find_node_with_prefix(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	for (; head; head = head->next)
	{
		p = starts_with(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (head);
	}

	return (NULL);
}

/**
 * get_node_index - Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t b = 0;

	for (; head; head = head->next, b++)
	{
		if (head == node)
			return (b);
	}

	return (-1);
}
