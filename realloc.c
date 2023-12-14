#include "shell.h"
#include <stdlib.h>  // Include standard library for memset

/**
* _memset - Fills memory with a constant byte.
* @s: Pointer to the memory area.
* @b: The byte to fill *s with.
* @n: The amount of bytes to be filled.
* Return: (s) a pointer to the memory area s.
*/
char *_memset(char *s, char b, unsigned int n)
{
return memset(s, b, n);
}

/**
* ffree - Frees a string of strings.
* @pp: String of strings.
*/
void ffree(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
* _realloc - Reallocates a block of memory.
* @ptr: Pointer to previous malloc'ated block.
* @old_size: Byte size of the previous block.
* @new_size: Byte size of the new block.
* Return: Pointer to the old block or a new block.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;

if (!ptr)
return malloc(new_size);

if (new_size == 0)
{
free(ptr);
return NULL;
}

p = malloc(new_size);
if (!p)
return NULL;

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];

free(ptr);
return p;
}
