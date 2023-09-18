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
	if (ptr)
	{
		/* Free the memory block */
		free(*ptr);
		/* Set the pointer to NULL to avoid a dangling pointer */
		*ptr = NULL;
		/* Return 1 to indicate successful memory deallocation */
		return (1);
	}

	/* Return 0 to indicate that no memory was freed */
	return (0);
}
