/*
** EPITECH PROJECT, 2019
** Malloc_buddy
** File description:
** free
*/

#include "../include/my_malloc.h"

inline void free_swap(block_t **block, block_t **buddy)
{
    block_t *tmp;

    if (block && buddy && block > buddy) {
        tmp = (*block);
        (*block) = (*buddy);
        (*buddy) = tmp;
    }
}

inline void remove_block(block_t *block)
{
    long order = (block) ? (long)block->kval : -1;
    block_t *current = (block && order != -1) ? blocks[order] : NULL;

    if (current == NULL || order == -1) {
        return;
    }
    if (current == block) {
        blocks[order] = current->succ;
        return;
    }
    for (;current->succ && current->succ != block; current = current->succ);
    (current->succ && current->succ->succ) ?
                                    current->succ = current->succ->succ : 0;
}

void free(void *ptr)
{
    block_t *block;
    block_t *buddy;

    if (ptr == NULL)
        return;
    block = (void *)ptr - BLOCK_SIZE;
    buddy = (void *)(pool + (BLOCK_SPL(block, pool) ^ (1 << block->kval)));
    block->status = FREE_BLOCK;
    for (; block->kval < MAX_KVAL_VALUE && buddy->status == FREE_BLOCK
                                            && buddy->kval == block->kval; ) {
        remove_block(buddy);
        free_swap(&block, &buddy);
        block->kval = ADD_ONE(block->kval);
        buddy = (void *)(pool + (BLOCK_SPL(block, pool) ^ (2 << block->kval)));
    }
    block->succ = blocks[block->kval];
    blocks[block->kval] = block;
}
