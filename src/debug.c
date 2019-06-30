/*
** EPITECH PROJECT, 2019
** Malloc_buddy
** File description:
** debug
*/

#include <stdarg.h>
#include <stdio.h>

void debug(const char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    vfprintf(stderr, format, vargs);
    va_end(vargs);
}