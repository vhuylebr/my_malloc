/*
** EPITECH PROJECT, 2018
** handle
** File description:
** handle
*/

#include "malloc.h"

void *handle_big_malloc(size_t size)
{
        t_link *tmp;

        tmp = all.free_list[256];
        all.free_list[256] = tmp->next;
        all.end->next = tmp;
        tmp->prev = all.end;
        tmp->next = NULL;
        if (tmp->size - size > (sizeof(t_link) + 16))
		free_big_malloc(tmp, size);
        tmp->size = size;
        tmp->is_free = 1;
        all.end = tmp;
        --all.ref_free[256];
        return (tmp->addr);
}

void *handle_big_malloc2(size_t size)
{
        t_link *tmp;

        tmp = all.free_list[256];
        all.free_list[256] = tmp->next;
        tmp->next = NULL;
        tmp->prev = NULL;
        if (tmp->size - size > (sizeof(t_link) + 16))
		free_big_malloc(tmp, size);
        tmp->size = size;
        tmp->is_free = 1;
        all.list = tmp;
        all.end = tmp;
        --all.ref_free[256];
        return (tmp->addr);
}

void *handle_tiny_malloc(size_t size, size_t index)
{
        t_link *tmp;

        tmp = all.free_list[index];
        tmp->is_free = 1;
        tmp->size = size;
        all.free_list[index] = tmp->next;
        --all.ref_free[index];
        tmp->prev = NULL;
        tmp->next = NULL;
        all.list = tmp;
        all.end = tmp;
        return (tmp->addr);
}
