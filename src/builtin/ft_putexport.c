/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putexport.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:50:29 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/03 11:07:56 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_env(char **arr, int i, size_t j)
{
	ft_putstr_fd("declare -x ", 1);
	if (arr[i][j] && arr[i][j + 1])
	{
		write(1, arr[i], j + 1);
		if (arr[i][j] == '=')
			ft_putstr_fd("\"", 1);
		ft_putstr_fd(&arr[i][j + 1], 1);
		if (arr[i][j] == '=')
			ft_putstr_fd("\"", 1);
	}
	else
		write(1, arr[i], j);
	ft_putstr_fd("\n", 1);
}

void	ft_putexport(char **env)
{
	char	**arr;
	int		i;
	size_t	j;

	i = -1;
	arr = ft_strsort_arr(env);
	if (!arr)
		return ;
	while (arr[++i])
	{
		if (arr[i][0] == '?' || (arr[i][0] == '_' && arr[i][1] == '='))
			continue ;
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			j++;
		ft_print_env(arr, i, j);
	}
	ft_free_array((void **)arr);
}
