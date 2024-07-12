/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_lvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 07:40:19 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/12 08:10:27 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_init_lvl(t_parse *parse)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (parse->task[i])
	{
		if (i == 0)
			count++;
		else if (parse->task[i]->lvl != parse->task[i - 1]->lvl)
			count++;
		i++;
	}
	parse->sub_lvl = ft_calloc(count + 1, sizeof(int[2]));
	if (!parse->sub_lvl)
		return (false);
	i = 0;
	while (i < count)
	{
		parse->sub_lvl[i][0] = -1;
		parse->sub_lvl[i][1] = -1;
		i++;
	}
	return (true);
}
