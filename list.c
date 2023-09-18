#include "shell.h"

/**
 * add_node - Inserts a new node at the beginning of the list.
 * @head:   Address of a pointer to the head node.
 * @str:    String field of the new node.
 * @num:    Index of the node used for history.
 *
 * Return: The size of the updated list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	/* Allocate memory for the new node */
	list_t *new_head;

	/* Check if head pointer is valid */
	if (!head)
		return (NULL);

	/* Create a new node and initialize its fields */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	/* Copy the string if it's provided */
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	/* Update the head pointer and return the new node */
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Appends a new node to the end of the list.
 * @head:   Address of a pointer to the head node.
 * @str:    String field of the new node.
 * @num:    Index of the node used for history.
 *
 * Return: The size of the updated list.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	/* Check if head pointer is valid */
	if (!head)
		return (NULL);

	/* Initialize pointers for traversal */
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	/* Copy the string if it's provided */
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	/* Append the new node to the end of the list */
	if (node)
	{
		for (; node->next; node = node->next)
			;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 * @h:  Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	/* Traverse the list and print the 'str' field of each node */
	for (; h; h = h->next, i++)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}

	return (i);
}

/**
 * delete_node_at_index - Deletes a node at a given index.
 * @head:   Address of a pointer to the first node.
 * @index:  Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	/* Check if head pointer is valid */
	if (!head || !*head)
		return (0);

	/* Handle deletion of the first node */
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	/* Traverse the list to find the node to delete */
	node = *head;
	for (; node; i++, prev_node = node, node = node->next)
	{
		if (i == index)
		{
			/* Update pointers and free memory for the deleted node */
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
	}

	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of a pointer to the head node.
 *
 * Return: Void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	/* Check if head pointer is valid */
	if (!head_ptr || !*head_ptr)
		return;

	/* Initialize pointers for traversal and deletion */
	head = *head_ptr;
	node = head;
	for (; node; node = next_node)
	{
		/* Save the next node, free memory for the current node */
		next_node = node->next;
		free(node->str);
		free(node);
	}

	/* Set the head pointer to NULL after all nodes are freed */
	*head_ptr = NULL;
}
