/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <vhuylebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:18:51 by vhuylebr          #+#    #+#             */
/*   Updated: 2018/02/10 14:01:44 by vhuylebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*handle_tiny_malloc2(size_t size, size_t index)
{
	t_link *tmp;

	tmp = g_all.free_list[index];
	tmp->is_free = 1;
	tmp->size = size;
	g_all.free_list[index] = tmp->next;
	--g_all.ref_free[index];
	tmp->prev = g_all.end;
	tmp->prev->next = tmp;
	g_all.end = tmp;
	g_all.end->next = NULL;
	return (tmp->addr);
}

void	*add_tiny_malloc(size_t size)
{
	int index;

	index = size / 16;
	if (g_all.ref_free[index] > 0)
		return (handle_tiny_malloc2(size, index));
	if (g_all.sum_allocated + ((size / 16 + 1) * 16)
			+ sizeof(t_link) >= g_all.size_page)
	{
		g_all.sum_allocated = 0;
		g_all.page = mmap(0, 4096 * 32,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_all.size_page = 4096 * 32;
	}
	g_all.end->next = g_all.page + g_all.sum_allocated;
	g_all.end->next->prev = g_all.end;
	g_all.end->next->size = size;
	g_all.end->next->addr = g_all.page + g_all.sum_allocated + sizeof(t_link);
	g_all.end->next->is_free = 1;
	g_all.sum_allocated = g_all.sum_allocated
		+ ((size / 16 + 1) * 16) + sizeof(t_link);
	g_all.end->next->next = NULL;
	g_all.end = g_all.end->next;
	return (g_all.end->addr);
}

void	*add_large_malloc(size_t size)
{
	void *tmp_page;

	if (g_all.ref_free[256] > 0)
	{
		if (g_all.free_list[256] && g_all.free_list[256]->size >= size)
			return (handle_big_malloc(size));
	}
	tmp_page = mmap(0, size + sizeof(t_link),
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	g_all.end->next = tmp_page;
	g_all.end->next->prev = g_all.end;
	g_all.end->next->size = size;
	g_all.end->next->addr = tmp_page + sizeof(t_link);
	g_all.end->next->is_free = 1;
	g_all.end->next->next = NULL;
	g_all.end = g_all.end->next;
	++g_all.nb_malloc;
	return (g_all.end->addr);
}

void	*malloc(size_t size)
{
	if (!size)
		return (0);
	if (g_all.list == NULL)
		return (first_block(size));
	if (size < 4096 - sizeof(t_link))
		return (add_tiny_malloc(size));
	return (add_large_malloc(size));
}
