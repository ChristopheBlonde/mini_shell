/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_lvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 07:40:19 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/17 17:00:14 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_def_sub(t_parse *parse, size_t n)
{
	size_t	i;
	size_t	j;
	t_lvl	lvl;

	i = 0;
	while (i < n)
	{
		lvl = parse->sub_lvl[i];
		j = lvl.befor + 1;
		while (j < (size_t)lvl.after)
		{
			parse->task[j]->i_sub = i;
			j++;
		}
		i++;
	}
}

static void	ft_init_lvl(t_parse *parse, size_t cur_sub, size_t i, size_t cur_o)
{
	t_lvl	lvl;
	int		open;

	open = cur_o;
	lvl.befor = (int)i - 1;
	while (parse->task[i + 1] && parse->task[i++])
	{
		if (parse->task[i]->open != 0)
			open += parse->task[i]->open;
		if (parse->task[i]->close != 0)
			open -= parse->task[i]->close;
		if (open <= 0)
			break ;
	}
	lvl.after = (int)i + 1;
	lvl.status = -1;
	parse->sub_lvl[cur_sub] = lvl;
}

static void	ft_open_sub_lvl(t_parse *parse)
{
	int	open;
	int	i;
	int	cur_sub;

	i = 0;
	cur_sub = 0;
	while (parse->task[i])
	{
		if (parse->task[i]->open != 0)
		{
			open = parse->task[i]->open;
			while (open > 0)
			{
				ft_init_lvl(parse, cur_sub, i, open);
				cur_sub++;
				open--;
			}
		}
		i++;
	}
}

bool	ft_init_sub_lvl(t_parse *parse)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (parse->task[i])
	{
		if (parse->task[i]->open != 0)
			count += parse->task[i]->open;
		i++;
	}
	parse->sub_lvl = ft_calloc(count + 1, sizeof(t_lvl));
	if (!parse->sub_lvl)
		return (false);
	parse->n_sub = count;
	ft_open_sub_lvl(parse);
	ft_def_sub(parse, count);
	return (true);
}
