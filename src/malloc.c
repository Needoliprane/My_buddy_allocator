/*
** EPITECH PROJECT, 2019
** Malloc_buddy
** File description:
** malloc
*/

#include "../include/my_malloc.h"

inline void split_adjust_i(size_t *i, block_t **block)
{
    if (block == NULL)
        return;
    for (; (*i) <= MAX_KVAL_VALUE; (*i) += 1) {
        if (blocks[(*i)] != NULL) {
            (*block) = blocks[(*i)];
            blocks[(*i)] = (*block)->succ;
            (*block)->succ = NULL;
            return;
        }
    }
}

inline void *split(size_t order)
{
    block_t *block = NULL;
    block_t *buddy = NULL;
    size_t i = ADD_ONE(order);

    split_adjust_i(&i, &block);
    if (block == NULL || block->kval > MAX_KVAL_VALUE || block->kval == 0) {
        return (NULL);
    }
    do {
        block->kval -= 1;
        buddy = (void *)(pool + (BLOCK_SPL(block, pool) ^ (2 << block->kval)));
        buddy->kval = block->kval;
        buddy->status = FREE_BLOCK;
        buddy->succ = blocks[block->kval];
        blocks[block->kval] = buddy;
    } while (block->kval != order);
    block->status = RESERVED;
    return (block->data);
}

inline void set_init(char **start, unsigned long offset, block_t **init)
{
    (*init) = blocks[MAX_KVAL_VALUE] = (void *)(*start + offset);
    pool = (char *)blocks[MAX_KVAL_VALUE];
    (*init)->status = FREE_BLOCK;
    (*init)->kval = MAX_KVAL_VALUE;
    (*init)->succ = NULL;
}

void *malloc(size_t size)
{
    block_t *init;
    block_t *block;
    char *start;
    size_t order = OTHER_CASE;

    if (size > 0 && pool == NULL) {
        start = (char *) sbrk((1 << MAX_KVAL_VALUE) + PADDING_STRUCT);
        set_init(&start, OFFSET(start), &init);
    }
    for (;size > 0 && (size_t)(1 << order) < (size + BLOCK_SIZE); order++);
    if (size > 0 && blocks[order] != NULL) {
        block = blocks[order];
        blocks[order] = block->succ;
        block->succ = NULL;
        block->status = RESERVED;
        return (block->data);
    }
    return ((size > 0) ? split(order) : NULL);
}

/*

Offset = distance séparant deux emplacements mémoire.

*/