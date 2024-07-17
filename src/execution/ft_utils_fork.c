/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:54:32 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/17 16:55:23 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_forks(t_parse *parse, size_t i, int status, size_t cur_sub)
{
	if (status == 1)
	{
		if (cur_sub != parse->task[i]->lvl)
			return ;
		if (i == 0)
			status = 0;
		else
			status = parse->task[i - 1]->status;
		ft_free_all(parse);
		exit(status);
	}
	if (status == 0 && cur_sub != 0
		&& parse->task[i] && parse->task[i]->close != 0)
	{
		status = parse->task[i]->status;
		ft_free_all(parse);
		exit(status);
	}
	if (status == 2 && i != 0 && cur_sub > parse->task[i]->lvl)
	{
		status = parse->task[i - 1]->status;
		ft_free_all(parse);
		exit(status);
	}
}
