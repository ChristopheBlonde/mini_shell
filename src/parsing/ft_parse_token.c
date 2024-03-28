/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/28 17:06:27 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO : classifier les tokens



void	ft_parse_token(t_parse *parse, char *input)
{
	size_t	i;
	char	**arr;

	(void)parse;
	i = 0;
	arr = ft_strtok(input, "<>|&\n");
	while (arr[i])
	{
		if (i == ft_arrlen((void **)arr) - 1)
			ft_putstr_fd(arr[i], 1);
		else
			ft_putendl_fd(arr[i], 1);
		i++;
	}
	ft_free_array((void **)arr);
}
