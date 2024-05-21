/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_temp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:28:07 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/21 20:16:25 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	add_env_to_list(t_list **new_list, t_list *current,
	t_stuff *stuff, t_env_handler env_handler)
{
	if (stuff->k == 0)
	{
		ft_lstadd_back(new_list, ft_lstnew(ft_strfjoin(
					ft_substr((char *)current->content, 0, stuff->z),
					env_handler.new_env[stuff->k], 1)));
		return ;
	}
	if (stuff->k + 1 == env_handler.new_env_len)
	{
		ft_lstadd_back(new_list, ft_lstnew(ft_strfjoin(
					env_handler.new_env[stuff->k], ft_substr(
						(char *)current->content, ft_strlen(
							stuff->var) + 1 + stuff->z,
						env_handler.var_end_size), 2)));
		return ;
	}
	ft_lstadd_back(new_list, ft_lstnew
		(ft_strdup(env_handler.new_env[stuff->k])));
}

void	add_env_to_new_list(t_list **new_list, t_list *current,
	t_stuff *stuff, t_env_handler *e)
{
	char	*temp;

	temp = NULL;
	temp = ft_strfjoin(ft_substr((char *)current->content,
				0, stuff->z), e->new_env[0], 1);
	temp = ft_strfjoin(temp, ft_substr((char *)current->content,
				ft_strlen(stuff->var) + 1 + stuff->z, e->var_end_size), 3);
	ft_lstadd_back(new_list, ft_lstnew(temp));
}
