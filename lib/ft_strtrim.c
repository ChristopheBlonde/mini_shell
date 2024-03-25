/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:16:17 by cblonde           #+#    #+#             */
/*   Updated: 2023/11/03 13:00:24 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_test_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_len;
	char	*str;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_test_set(s1[i], set))
		s1++;
	s1_len = ft_strlen(s1);
	while (s1_len > 0 && ft_test_set(s1[s1_len - 1], set))
		s1_len--;
	str = ft_calloc(s1_len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	return (str);
}
