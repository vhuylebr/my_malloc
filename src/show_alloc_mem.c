/*
** EPITECH PROJECT, 2018
** show
** File description:
** show
*/

#include "malloc.h"

void ft_putnbr(int nb)
{
	int i;

	if (nb < 0) {
		write(1, "-", 1);
		nb = nb * -1;
	}
	i = nb;
	if (i >= 10)
		ft_putnbr(i / 10);
	i = i % 10 + '0';
	write(1, &i, 1);
}

void show_alloc_mem()
{
        t_link *tmp;
        int i = 0;

	printf("break : %p\n", sbrk(0));
        tmp = all.list;
        while (tmp != NULL) {
                if (tmp->is_free != 0) {
			printf("%p - %p : %u bytes\n", tmp->addr,
                                tmp->addr + tmp->size, tmp->size);
                        ++i;
                }
                tmp = tmp->next;
	}
}
