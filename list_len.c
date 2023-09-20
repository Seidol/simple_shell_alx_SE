#include "shell.h"

/**
 * list_len - Computes the length of a linked list.
 * @head: Pointer to the first node of the list.
 *
 * This function calculates the size of a linked list by iterating
 * through its nodes. It takes the address of the first node
 * as an argument and returns the total number of nodes in the list.
 *
 * Return: The number of nodes in the list.
 */

size_t list_len(const list_t *head)
{
	size_t size = 0;

	for (; head; head = head->next)
		size++;

	return (size);
}

/**
 * list_to_strings - Converts a linked list of strings into an array of strings
 * @head: Pointer to the first node of the list.
 *
 * This function transforms a linked list of strings into a dynamically
 * allocated array of strings. It takes the address of the first node
 * as an argument and returns the resulting array of strings.
 *
 * Return: An array of strings.
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < a; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - Displays all elements of a list_t linked list.
 * @head: Pointer to the first node of the list.
 *
 * This function prints out all the elements in a linked list of type
 * list_t. It takes the address of the first node as an argument
 * and returns the size of the list.
 *
 * Return: The size of the list.
 */

size_t print_list(const list_t *head)
{
	size_t size = 0;

	for (; head; head = head->next, size++)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
	}

	return (size);
}

/**
 * node_starts_with - Locates a node in the list whose string
 * starts with a specified prefix.
 * @node: Pointer to the head of the list.
 * @prefix: The prefix string to match.
 * @c: The character after the prefix to match.
 *
 * This function searches the linked list for a node whose string
 * starts with the provided prefix, followed by the specified character.
 * It takes the head of the list, the prefix string, and the character after
 * the prefix as arguments. If a match is found,
 * it returns the matching node; otherwise, it returns NULL.
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Retrieves the index of a node in the linked list.
 * @head: Pointer to the head of the list.
 * @node: Pointer to the node.
 *
 * This function determines the index of a given node in the linked
 * list. It takes the head of the list and the node's
 * pointer as arguments. If the node is found,
 * it returns its index; otherwise, it returns -1.
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
