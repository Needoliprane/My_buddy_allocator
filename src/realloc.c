/*
** EPITECH PROJECT, 2019
** Malloc_buddy
** File description:
** realloc
*/

#include "../include/my_malloc.h"

void *realloc(void *ptr, size_t size)
{
    size_t old_siz = 0;
    block_t *old_alloc = (ptr) ? (void *)((char *)ptr - BLOCK_SIZE) : NULL;
    char *new_alloc = NULL;

    if (ptr == NULL || (new_alloc = (size > 0) ? malloc(size) : NULL) == NULL)
        return (NULL);
    old_siz = (1 << old_alloc->kval) - BLOCK_SIZE;
    for (size_t i = 0; i < old_siz && i < size; i++,
                                            new_alloc[i] = old_alloc->data[i]);
    free(ptr);
    return (new_alloc);
}