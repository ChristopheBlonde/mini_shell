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

static char	**ft_dupentries(char *s1, char *s2)
{
	char	**arr;

	if (!s2 || !s2)
		return (NULL);
	arr = (char **)ft_calloc(3, sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup(s1);
	if (!arr[0])
	{
		free(arr);
		return (NULL);
	}
	arr[1] = ft_strdup(s2);
	if (!arr[1])
	{
		ft_free_array((void **)arr);
		return (NULL);
	}
	return (arr);
}

static void	ft_arrtolower(char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			arr[i][j] = ft_tolower(arr[i][j]);
			j++;
		}
		i++;
	}
}

static bool	ft_isfirst(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	**strs;
	bool	result;

	strs = ft_dupentries(s1, s2);
	if (!strs)
		return (true);
	i = 0;
	j = 0;
	while (strs[0][i] && !ft_isalpha(strs[0][i]))
		i++;
	while (strs[1][j] && !ft_isalpha(strs[1][j]))
		j++;
	ft_arrtolower(strs);
	while (strs[0] && strs[1] && strs[0][i] == strs[1][j] && i++ && j++)
		;
	result = strs[0][i] > strs[1][j];
	ft_free_array((void **)strs);
	return (result);
}

static void	ft_lstswap(t_list *lst)
{
	void	*tmp;

	tmp = NULL;
	tmp = lst->content;
	lst->content = lst->next->content;
	lst->next->content = tmp;
}

void	ft_sortwc(t_list **lst)
{
	char	*s1;
	char	*s2;
	t_list	*current;
	int		i;

	i = -1;
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
				ft_lstswap(current);
			current = current->next;
		}
	}
}
