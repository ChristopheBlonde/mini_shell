/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:33:13 by cblonde           #+#    #+#             */
/*   Updated: 2023/11/03 11:15:27 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	str_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_len = s1_len + s2_len + 1;
	str = ft_calloc(str_len, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_strlcat(str, s2, str_len);
	return (str);
}
