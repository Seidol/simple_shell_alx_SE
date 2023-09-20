#include "shell.h"

/**
 * _memset - Fills a memory block with a specific byte.
 * @s: Pointer to the memory block.
 * @b: The byte to fill the memory with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the filled memory block.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a = 0;

	do {
		s[a] = b;
		a++;
	} while (a < n);

	return (s);
}

/**
 * ffree - Frees a list of strings and the list itself.
 * @pp: The list of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	do {
		free(*pp);
		pp++;
	} while (*pp);

	free(a);
}

/**
 * _realloc - Reallocates a block of memory with a new size.
 * @ptr: Pointer to the previous memory block.
 * @old_size: Size of the previous block in bytes.
 * @new_size: Size of the new block in bytes.
 *
 *	Return: Pointer to the newly allocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);

	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	do {
		p[old_size - 1] = ((char *)ptr)[old_size - 1];
		old_size--;
	} while (old_size);

	free(ptr);

	return (p);
}
