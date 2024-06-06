/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:54:56 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/06 13:56:22 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	if ((size_t)start >= ft_strlen(s))
	{
		str = ft_calloc(1, sizeof(char));
		if (str == NULL)
			return (NULL);
		return (str);
	}
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, ((unsigned char *)s + start), len);
	return (str);
}
