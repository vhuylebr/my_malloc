/*
** EPITECH PROJECT, 2018
** realloc
** File description:
** realloc
*/

#include "malloc.h"

void  *realloc(void *ptr, size_t size)
{
	t_link *tmp_link;
	void *tmp_page;

        if (size == 0 && ptr) {
        	free(ptr);
        	return (NULL);
        }
        if (size > 0 && !ptr)
        	return (malloc(size));
        if (size == 0 && !ptr)
        	return (NULL);
        tmp_link = ptr - sizeof(t_link);
        tmp_page = malloc(size);
        free(ptr);
        if (tmp_link->size < size)
                memcpy(tmp_page, ptr, tmp_link->size);
        else
                memcpy(tmp_page, ptr, size);
        return (tmp_page);
}
