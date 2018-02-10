/*
** EPITECH PROJECT, 2018
** malloc.c
** File description:
** malloc.c
*/

#include "malloc.h"

void *handle_tiny_malloc2(size_t size, size_t index)
{
        t_link *tmp;

        tmp = all.free_list[index];
        tmp->is_free = 1;
        tmp->size = size;
        all.free_list[index] = tmp->next;
        --all.ref_free[index];
        tmp->prev = all.end;
        tmp->prev->next = tmp;
        all.end = tmp;
        all.end->next = NULL;
        return (tmp->addr);
}

void *add_tiny_malloc(size_t size)
{
        int index = size / 16;

        if (all.ref_free[index] > 0)
                return (handle_tiny_malloc2(size, index));
        if (all.sum_allocated + ((size / 16 + 1) * 16)
			+ sizeof(t_link) >= all.size_page) {
                all.sum_allocated = 0;
                all.page = sbrk(4096 * 32);
                all.size_page = 4096 * 32;
        }
        all.end->next = all.page + all.sum_allocated;
        all.end->next->prev = all.end;
        all.end->next->size = size;
        all.end->next->addr = all.page + all.sum_allocated + sizeof(t_link);
        all.end->next->is_free = 1;
        all.sum_allocated = all.sum_allocated
		+ ((size / 16 + 1) * 16) + sizeof(t_link);
        all.end->next->next = NULL;
        all.end = all.end->next;
        return (all.end->addr);
}

void *add_large_malloc(size_t size)
{
        void *tmp_page;

        if (all.ref_free[256] > 0) {
                if (all.free_list[256] && all.free_list[256]->size >= size)
                        return (handle_big_malloc(size));
        }
        tmp_page = sbrk(size + sizeof(t_link) + 4096);
        all.end->next = tmp_page;
        all.end->next->prev = all.end;
        all.end->next->size = size;
        all.end->next->addr = tmp_page + sizeof(t_link);
        all.end->next->is_free = 1;
        all.end->next->next = NULL;
        all.end = all.end->next;
        ++all.nb_malloc;
        return (all.end->addr);
}

void *malloc(size_t size)
{
	if (!size)
		return (0);
        if (all.list == NULL)
        	return first_block(size);
        if (size < 4096 - sizeof(t_link))
        	return (add_tiny_malloc(size));
        return (add_large_malloc(size));
}
