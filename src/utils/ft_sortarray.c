/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortarray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:43:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/09 18:52:11 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_strarrcpy(char **arr)
{
	size_t	len;
	size_t	i;
	char	**n_arr;

	i = 0;
	len = ft_arrlen((void **)arr);
	n_arr = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!n_arr)
		return (NULL);
	while (arr[i])
	{
		n_arr[i] = ft_strdup(arr[i]);
		if (!n_arr[i])
		{
			ft_free_array((void **)n_arr);
			return (NULL);
		}
		i++;
	}
	return (n_arr);
}

static void	ft_swap_strarr(char **arr, int i, int j)
{
	char	*tmp;

	tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

char	**ft_strsort_arr(char **arr)
{
	char	**n_arr;
	int		i;
	int		j;
	int		k;
	size_t	len;

	i = -1;
	n_arr = ft_strarrcpy(arr);
	len = ft_arrlen((void **)n_arr);
	if (!n_arr)
		return (NULL);
	while (++i < (int)len)
	{
		j = i;
		while (n_arr[++j])
		{
			k = 0;
			while (n_arr[i][k] == n_arr[j][k])
				k++;
			if (n_arr[i][k] > n_arr[j][k])
				ft_swap_strarr(n_arr, i, j);
		}
	}
	return (n_arr);
}
