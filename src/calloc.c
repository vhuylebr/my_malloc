/*
** EPITECH PROJECT, 2018
** calloc
** File description:
** calloc
*/

#include "malloc.h"

void *calloc(size_t nmemb, size_t size)
{
	if (!nmemb || !size)
		return (NULL);
	return (malloc(nmemb * size));
}
