/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:43:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/02 16:40:15 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_lstto_arr(t_object **task, t_list *lst, int i)
{
	size_t	j;
	size_t	lst_len;
	t_list	*tmp;
	char	**n_arr;

	j = 0;
	lst_len = ft_lstsize(lst);
	n_arr = (char **)ft_calloc(lst_len + 1, sizeof(char *));
	if (!n_arr)
	{
		ft_lstclear(&lst, free);
		return ;
	}
	while (lst)
	{
		n_arr[j] = lst->content;
		tmp = lst;
		lst = lst->next;
		free(tmp);
		j++;
	}
	free(lst);
	ft_free_array((void **)task[i]->cmd);
	task[i]->cmd = n_arr;
}

t_list	*ft_suppdouble(t_list *lst)
{
	t_list	*n_lst;
	t_list	*current;
	t_list	*tmp;
	bool	present;

	n_lst = NULL;
	tmp = lst;
	present = false;
	while (tmp)
	{
		current = n_lst;
		while (current)
		{
			if (!ft_strncmp(tmp->content, current->content,
					ft_strlen(current->content)))
				present = true;
			current = current->next;
		}
		if (!present)
			ft_lstadd_back(&n_lst, ft_lstnew(ft_strdup(tmp->content)));
		present = false;
		tmp = tmp->next;
	}
	ft_lstclear(&lst, free);
	return (n_lst);
}
