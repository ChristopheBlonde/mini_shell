/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:56:02 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/29 10:07:28 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_arrcpy(char ***arr, char **new_arr, size_t *i)
{
	while ((*arr)[*i])
	{
		new_arr[*i] = ft_strdup((*arr)[*i]);
		if (!new_arr[*i])
		{
			ft_free_array(*(void **)new_arr);
			return ;
		}
		*i += 1;
	}
}

static void	ft_tokcpy(char ***arr, char *str, size_t n)
{
	char	**new_arr;
	size_t	arr_len;
	size_t	i;

	i = 0;
	arr_len = ft_arrlen(*(void **)arr);
	new_arr = (char **)ft_calloc(arr_len + 2, sizeof(char *));
	if (!new_arr)
		return ;
	ft_arrcpy(arr, new_arr, &i);
	new_arr[i] = (char *)ft_calloc(n + 1, sizeof(char));
	if (!new_arr[i])
	{
		ft_free_array((void **)new_arr);
		return ;
	}
	ft_memcpy((void *)new_arr[i], (void *)str, n);
	ft_free_array(*(void **)arr);
	*arr = new_arr;
}

char	**ft_strtok(char *str, char *tok)
{
	char	**arr;
	size_t	i;
	size_t	j;
	size_t	last;

	i = -1;
	last = 0;
	arr = (char **)ft_calloc(1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (str[++i])
	{
		j = -1;
		while (tok[++j])
		{
			if (i != 0 && str[i] == tok[j])
			{
				ft_tokcpy(&arr, &str[last], i - last);
				last = i;
				if (str[i + 1] == tok[j])
					i++;
			}
		}
	}
	return (arr);
}
