/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <vhuylebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:18:22 by vhuylebr          #+#    #+#             */
/*   Updated: 2018/02/10 14:18:56 by vhuylebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/mman.h>

typedef struct		s_link
{
	char			is_free;
	struct s_link	*next;
	struct s_link	*prev;
	unsigned int	size;
	void			*addr;
}					t_link;

typedef struct		s_type
{
	t_link			*list;
	void			*page;
	size_t			size_page;
	size_t			sum_allocated;
	size_t			nb_malloc;
	t_link			*free_list[257];
	int				ref_free[257];
	t_link			*end;
}					t_type;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();
void				free_big_malloc(t_link *cur, size_t size);
void				*first_block(size_t size);
void				*handle_big_malloc(size_t size);
void				*handle_tiny_malloc(size_t size, size_t index);
void				*handle_big_malloc2(size_t size);

t_type				g_all;

#endif
