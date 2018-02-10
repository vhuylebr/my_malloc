/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <vhuylebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:18:37 by vhuylebr          #+#    #+#             */
/*   Updated: 2018/02/10 14:01:44 by vhuylebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*first_block_add(size_t size)
{
	g_all.list->next = NULL;
	g_all.list->prev = NULL;
	g_all.list->size = size;
	g_all.list->is_free = 1;
	g_all.end = g_all.list;
	return (g_all.list->addr);
}

void	*first_large_block(size_t size)
{
	void *tmp_page;

	tmp_page = NULL;
	if (g_all.ref_free[256] > 0)
	{
		if (g_all.free_list[256]->size >= size)
			return (handle_big_malloc2(size));
	}
	tmp_page = mmap(0, size + sizeof(t_link),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	g_all.size_page = 0;
	g_all.list = tmp_page;
	g_all.list->addr = tmp_page + sizeof(t_link);
	return (first_block_add(size));
}

void	*first_tiny_block(size_t size)
{
	int index;

	index = size / 16;
	if (g_all.ref_free[index] > 0)
		return (handle_tiny_malloc(size, index));
	if (g_all.sum_allocated + ((size / 16 + 1) * 16) +
			sizeof(t_link) >= g_all.size_page)
	{
		g_all.sum_allocated = 0;
		g_all.page = mmap(0, 4096 * 32,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_all.size_page = 4096 * 32;
	}
	g_all.list = g_all.page;
	g_all.sum_allocated = g_all.sum_allocated
		+ ((size / 16 + 1) * 16) + sizeof(t_link);
	g_all.list->addr = g_all.page + sizeof(t_link);
	return (first_block_add(size));
}

void	*first_block(size_t size)
{
	if (size > 4096)
		return (first_large_block(size));
	return (first_tiny_block(size));
}
