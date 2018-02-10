/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <vhuylebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:34:22 by vhuylebr          #+#    #+#             */
/*   Updated: 2018/02/10 14:01:44 by vhuylebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*handle_big_malloc(size_t size)
{
	t_link *tmp;

	tmp = g_all.free_list[256];
	g_all.free_list[256] = tmp->next;
	g_all.end->next = tmp;
	tmp->prev = g_all.end;
	tmp->next = NULL;
	if (tmp->size - size > (sizeof(t_link) + 16))
		free_big_malloc(tmp, size);
	tmp->size = size;
	tmp->is_free = 1;
	g_all.end = tmp;
	--g_all.ref_free[256];
	return (tmp->addr);
}

void	*handle_big_malloc2(size_t size)
{
	t_link *tmp;

	tmp = g_all.free_list[256];
	g_all.free_list[256] = tmp->next;
	tmp->next = NULL;
	tmp->prev = NULL;
	if (tmp->size - size > (sizeof(t_link) + 16))
		free_big_malloc(tmp, size);
	tmp->size = size;
	tmp->is_free = 1;
	g_all.list = tmp;
	g_all.end = tmp;
	--g_all.ref_free[256];
	return (tmp->addr);
}

void	*handle_tiny_malloc(size_t size, size_t index)
{
	t_link *tmp;

	tmp = g_all.free_list[index];
	tmp->is_free = 1;
	tmp->size = size;
	g_all.free_list[index] = tmp->next;
	--g_all.ref_free[index];
	tmp->prev = NULL;
	tmp->next = NULL;
	g_all.list = tmp;
	g_all.end = tmp;
	return (tmp->addr);
}
