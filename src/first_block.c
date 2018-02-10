/*
** EPITECH PROJECT, 2018
** first.c
** File description:
** first.c
*/

#include "malloc.h"

void *first_block_add(size_t size)
{
        all.list->next = NULL;
        all.list->prev = NULL;
        all.list->size = size;
        all.list->is_free = 1;
        all.end = all.list;
        return (all.list->addr);
}

void *first_large_block(size_t size)
{
        void *tmp_page = NULL;

        if (all.ref_free[256] > 0) {
                if (all.free_list[256]->size >= size)
                        return (handle_big_malloc2(size));
        }
        tmp_page = sbrk(size + sizeof(t_link) + 4096);
        all.size_page = 0;
        all.list = tmp_page;
        all.list->addr = tmp_page + sizeof(t_link);
        return (first_block_add(size));
}

void *first_tiny_block(size_t size)
{
        int index = size / 16;

        if (all.ref_free[index] > 0)
                return (handle_tiny_malloc(size, index));
        if (all.sum_allocated + ((size / 16 + 1) * 16) +
			sizeof(t_link) >= all.size_page) {
                all.sum_allocated = 0;
                all.page = sbrk(4096 * 32);
                all.size_page = 4096 * 32;
        }
        all.list = all.page;
        all.sum_allocated = all.sum_allocated
		+ ((size / 16 + 1) * 16) + sizeof(t_link);
        all.list->addr = all.page + sizeof(t_link);
        return (first_block_add(size));
}

void  *first_block(size_t size)
{
        if (size > 4096)
                return (first_large_block(size));
        return (first_tiny_block(size));
}
