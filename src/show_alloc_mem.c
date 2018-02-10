/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <vhuylebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:20:52 by vhuylebr          #+#    #+#             */
/*   Updated: 2018/02/10 14:01:44 by vhuylebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem(void)
{
	t_link	*tmp;
	int		i;

	i = 0;
	printf("break : %p\n", g_all.list->addr);
	tmp = g_all.list;
	while (tmp != NULL)
	{
		if (tmp->is_free != 0)
		{
			printf("%p - %p : %u bytes\n", tmp->addr,
				tmp->addr + tmp->size, tmp->size);
			++i;
		}
		tmp = tmp->next;
	}
}
