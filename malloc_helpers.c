#include "shell.h"

/**
 * _memset - Fills a block of memory with a specified value.
 * @s: Pointer to the memory area.
 * @b: The byte value to be filled in the memory.
 * @n: The number of bytes to be filled.
 *
 * This function sets the first n bytes of the memory
 * area pointed by s to the specified value b.
 * Return: A pointer to the memory area s.
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - Frees a dynamically allocated array of strings.
 * @pp: Pointer to the array of strings.
 *
 * This function releases the memory occupied by the array of strings.
 */

void ffree(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 * _realloc - Reallocates a previously allocated block of memory.
 * @ptr: Pointer to the previously allocated block.
 * @old_size: Size of the previous block in bytes.
 * @new_size: Size of the new block in bytes.
 *
 * Return: Pointer to the reallocated block of memory.
 *
 * This function changes the size of the memory block
 * pointed to by ptr to new_size bytes.
 * The contents will be unchanged in the range from
 * the start of the region up to the minimum
 * of the old and new sizes. If the new_size is larger,
 * the added memory will not be initialized.
 * If ptr is NULL, the call is equivalent to malloc(new_size),
 * for all values of old_size and new_size.
 * If new_size is zero, the call is equivalent to free(ptr).
 * Unless ptr is NULL, it must have been
 * returned by an earlier call to malloc(), calloc() or realloc().
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
