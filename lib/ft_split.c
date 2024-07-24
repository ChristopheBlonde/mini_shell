/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:01:24 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/24 10:02:36 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_count_letters(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	ft_freearray(void **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**ft_implement_array(char **array, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word_len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word_len = ft_count_letters((char *)s + i, c);
			array[j] = ft_calloc(word_len + 1, sizeof(char));
			if (array[j] == NULL)
			{
				ft_freearray((void **)array);
				return (NULL);
			}
			ft_memcpy(array[j], (char *)s + i, word_len);
			i += ft_strlen(array[j]);
			j++;
		}
		else
			i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	return (ft_implement_array(array, s, c));
}
