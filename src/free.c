/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <vhuylebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:19:09 by vhuylebr          #+#    #+#             */
/*   Updated: 2018/02/10 15:24:59 by vhuylebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	add_free_node(t_link **tmp)
{
	if (g_all.list == *tmp)
		g_all.list = (*tmp)->next;
	if (g_all.end == *tmp)
		g_all.end = (*tmp)->prev;
	if ((*tmp)->next && (*tmp)->size != 27640 && (*tmp)->size != 23320)
		(*tmp)->next->prev = (*tmp)->prev;
	if ((*tmp)->prev != NULL && (*tmp)->size != 27640
			&& (*tmp)->size != 23320)
		(*tmp)->prev->next = (*tmp)->next;
}

void	free_tiny(size_t index, t_link **tmp)
{
	if (g_all.ref_free[index] == 0)
	{
		++g_all.ref_free[index];
		(*tmp)->next = NULL;
		(*tmp)->prev = NULL;
		g_all.free_list[index] = (*tmp);
	}
	else
	{
		++g_all.ref_free[index];
		(*tmp)->next = g_all.free_list[index];
		(*tmp)->next->prev = (*tmp);
		(*tmp)->prev = NULL;
		g_all.free_list[index] = (*tmp);
	}
}

void	free_large(t_link **tmp)
{
	if (g_all.free_list[256] == NULL)
	{
		++g_all.ref_free[256];
		(*tmp)->next = NULL;
		(*tmp)->prev = NULL;
		g_all.free_list[256] = *tmp;
	}
	else
	{
		++g_all.ref_free[256];
		(*tmp)->next = g_all.free_list[256];
		g_all.free_list[256]->prev = *tmp;
		(*tmp)->prev = NULL;
		g_all.free_list[256] = *tmp;
	}
}

void	free_big_malloc(t_link *cur, size_t size)
{
	t_link *data_to_free;

	data_to_free = cur->addr + size;
	data_to_free->size = cur->size - size - sizeof(t_link);
	data_to_free->is_free = 1;
	data_to_free->addr = cur->addr + size + sizeof(t_link);
	free(data_to_free->addr);
}

void	free(void *ptr)
{
	t_link	*tmp;
	size_t	index;

	if (!ptr)
		return ;
	if ((unsigned long long int)ptr > (unsigned long long int)g_all.end->addr ||
		(unsigned long long int)ptr < (unsigned long long int)g_all.list->addr)
		return ;
	tmp = ptr - sizeof(t_link);
	if (tmp->size == 0)
		return ;
	if (tmp->is_free == 0)
		write(2, "Already free\n", 13);
	else
	{
		tmp->is_free = 0;
		index = tmp->size / 16;
		add_free_node(&tmp);
		if (index < 256)
			free_tiny(index, &tmp);
		else
			free_large(&tmp);
	}
}
