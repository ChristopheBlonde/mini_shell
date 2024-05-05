/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:43:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/02 16:40:15 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_wc	*ft_init_wc(void)
{
	t_wc	*wc;

	wc = (t_wc *)ft_calloc(1, sizeof(t_wc));
	if (!wc)
		return (NULL);
	wc->start = NULL;
	wc->middle = NULL;
	wc->end = NULL;
	wc->i = -1;
	wc->quote = -1;
	wc->len = 0;
	return (wc);
}

void	ft_free_wc(t_wc *wc)
{
	if (!wc)
		return ;
	if (wc->start)
	{
		free(wc->start);
		wc->start = NULL;
	}
	if (wc->end)
	{
		free(wc->end);
		wc->end = NULL;
	}
	if (wc->middle)
		ft_lstclear(&wc->middle, free);
	free(wc);
}

void	ft_unquote(t_wc *wc)
{
	t_list	*current;

	current = wc->middle;
	if (wc->start && ft_quoted(wc->start))
		wc->start = ft_strqcpy(wc->start);
	if (wc->end && ft_quoted(wc->end))
		wc->end = ft_strqcpy(wc->end);
	while (current)
	{
		if (ft_quoted(current->content))
			current->content = ft_strqcpy(current->content);
		current = current->next;
	}
}

void	ft_lstinsert(t_list **lst, t_list *addlst, t_list **ptr)
{
	t_list	*current;
	t_list	*last;
	t_list	*tmp;

	current = (t_list *)*lst;
	last = ft_lstlast(addlst);
	tmp = *ptr;
	if (!addlst)
		return ;
	if (current != tmp)
		while (current->next != tmp)
			current = current->next;
	current->next = addlst;
	ft_lstadd_back(&addlst, tmp->next);
	free(tmp->content);
	free(*ptr);
	*ptr = last;
}
