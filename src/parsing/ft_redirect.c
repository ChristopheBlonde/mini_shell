/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:01:13 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/11 10:19:23 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_redirect(char *cmd)
{
	if (!ft_strncmp(cmd, ">", 1) || !ft_strncmp(cmd, ">>", 2)
			|| !ft_strncmp(cmd, "<", 1) || !ft_strncmp(cmd, "<<", 2))
		return (true);
	return (false);
}

static t_file_descriptor	**ft_realloc_redirect(t_file_descriptor **arr)
{
	t_file_descriptor	**new_arr;
	size_t				arr_len;
	size_t				i;

}

void	ft_redirection(t_parse *parse)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	parse->redirect = (t_file_descriptor)ft_calloc(1, t_file_descriptor);
	if (!parse->redirect)
		return ;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			ft_printf("i:%d, j:%d -> arg:%s\n", i, j, parse->task[i]->cmd[j]);
			if (ft_is_redirect(parse->task[i]->cmd[j]))
			{
				
			}
			j++;
		}
		i++;
	}
}
