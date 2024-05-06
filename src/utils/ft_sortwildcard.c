/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortwildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:43:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/02 16:40:15 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstget_prev(t_list **lst, t_list *target)
{
	t_list	*current;

	if (!lst || !target)
		return ;
	current = (t_list *)*lst;
	if (current == target)
		return (target);
	while (current->next != target)
		current = current->next;
	return (current);
}

bool	ft_alpha_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	ft_isfirst(t_list *a, t_list *b)
{
	char	*s1;
	char	*s2;

	if (!a || !b)
		return (true);
	s1 = (char *)a->content;
	s2 = (char *)b->content;

}

void	ft_sortwc(t_list *lst)
{
	
}
