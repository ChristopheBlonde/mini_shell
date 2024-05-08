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

	current = NULL;
	if (!lst || !target)
		return (current);
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

bool	ft_isfirst(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	int		k;

	if (!s1 || !s2)
		return (true);
	i = 0;
	j = 0;
	while (s1 && !ft_isalpha(s1[i]))
		i++;
	while (s2 && !ft_isalpha(s2[j]))
		j++;
	k = i - 1;
	while (s1 && s1[++k])
		s1[k] = ft_tolower(s1[k]);
	k = j - 1;
	while (s2 && s2[++k])
		s2[k] = ft_tolower(s2[k]);
	while (s1 && s2 && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	if (s1[i] > s2[j])
		return (true);
	return (false);
}

void	ft_sortwc(t_list **lst)
{
	char	*s1;
	char	*s2;
	void	*tmp;
	t_list	*current;
	int		i;

	tmp = NULL;
	i = -1;
	t_list *curr = *lst;
	while (curr)
	{
		ft_putendl_fd("------------", 1);
		ft_putendl_fd(curr->content, 1);
		ft_putendl_fd("____________", 1);
		curr = curr->next;
	}
	while (++i < ft_lstsize(*lst))
	{
		current = *lst;
		while (current)
		{
			s1 = current->content;
			if (current->next)
				s2 = current->next->content;
			else
				s2 = NULL;
			if (s2 && ft_isfirst(s1, s2))
			{
				tmp = current->content;
				current->content = current->next->content;
				current->next->content = tmp;
			}
			current = current->next;
		}
	}
	curr = *lst;
	while (curr)
	{
		ft_putendl_fd("------------", 1);
		ft_putendl_fd(curr->content, 1);
		ft_putendl_fd("------------", 1);
		curr = curr->next;
	}
}
