/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:51:54 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/11 10:17:23 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
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
	ft_memcpy(ptr, new_ptr, currsize);
	free(ptr);
	ptr = new_ptr;
	return (ptr);
}
