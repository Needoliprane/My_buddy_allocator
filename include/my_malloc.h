/*
** EPITECH PROJECT, 2019
** Malloc_buddy
** File description:
** my_malloc
*/

#ifndef MY_MALLOC_H_
#define MY_MALLOC_H_

/* Include */
#include <unistd.h>
#include <pthread.h>

/* Define & Macro */
#define FREE_BLOCK                  (0)
#define RESERVED                    (1)
#define OTHER_CASE                  (2)
#define MAX_KVAL_VALUE              (26)
#define PADDING_STRUCT              (sizeof(double) - 1)
#define BLOCK_SIZE                  (sizeof(block_t))
#define BLOCK_SPL(block, pool)      ((char *)block - pool)
#define ADD_ONE(order)              (order + 1)
#define OFFSET(start)               ((unsigned long)start % sizeof(double))

/* Struct */
typedef struct block_t block_t;
struct block_t {
    unsigned status: 1; /* RESERVED FREE */
    size_t kval;
    block_t *succ;
    char data[];
};

/* Declare and set*/
static block_t *blocks[MAX_KVAL_VALUE + 1] = {0};
static char *pool = NULL;

/* Main Prototypes */
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

/* Tool ==> Malloc */
void *split(size_t order);
void split_adjust_i(size_t *i, block_t **block);
void set_init(char **start, unsigned long offset, block_t **init);

/* Tool ==> Free */
void remove_block(block_t *block);
void free_swap(block_t **block, block_t **buddy);

/* Debug */
void debug(const char *format, ...);

#endif /* !MY_MALLOC_H_ */
