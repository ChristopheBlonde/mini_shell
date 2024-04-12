/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:51:54 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/11 11:06:05 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	currsize;

	if (!size)
		return (ptr);
	if (!ptr)
		return (ft_calloc(1, size));
	currsize = sizeof(ptr);
	if (size <= currsize)
		return (ptr);
	new_ptr = ft_calloc(1, size);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, currsize);
	free(ptr);
	ptr = new_ptr;
	return (ptr);
}*/
static size_t ft_malloc_usable_size(void *ptr)
{
    size_t *header = (size_t *)ptr - 1;
    return *header & ~0x1;
}


void    *ft_realloc(void *ptr, size_t size)
{
    void    *new_ptr;
    size_t    currsize;

    if (!size)
    {
        free(ptr);
        return NULL;
    }
    if (ptr == 0)
        return ft_calloc(1, size);
    currsize = ft_malloc_usable_size(ptr);
    if (size <= currsize)
        return ptr;
    new_ptr = ft_calloc(1, size);
    if (!new_ptr)
    {
        free(ptr);
        return NULL;
    }
    ft_memcpy(new_ptr, ptr, currsize);
    free(ptr);
    return new_ptr;
}
