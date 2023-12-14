#include "shell.h"

/**
 * bfree - Frees a pointer and NULLs the address.
 * @ptr: Address of the pointer to free.
 *
 * Return: EXIT_SUCCESS if freed successfully, EXIT_FAILURE otherwise.
 */
int bfree(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
