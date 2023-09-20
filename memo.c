#include "shell.h"

/**
 * bfree - Frees a memory block and sets the pointer to NULL.
 * @ptr: Address of the pointer to free.
 *
 *	This function deallocates the memory block pointed to by 'ptr' and
 *	updtes the pointer to NULL to prevent it from bcming a dangling pointer
 *
 *	Return: 1 if memory was successfully freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
