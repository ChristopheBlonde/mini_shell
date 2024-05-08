/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:43:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/02 16:40:15 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	ft_check_wildcard(char *args)
{
	size_t	i;
	char quote;

	i = 0;
	quote = '\0';
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '"')
		{
			if (quote == args[i])
				quote = '\0';
			else
				quote = args[i];
		}
		else if (args[i] == '*' && !quote)
			return (true);
		i++;
	}
	return (false);
}

static bool	ft_match_start(t_wc *wc, char *str, char **file)
{
	size_t	len;

	if (wc->start && str[0] == *file[0])
	{
		len = ft_strlen(wc->start);
		if (!ft_strncmp(*file, wc->start, len))
		{
			*file += len;
			return (true);
		}
		else
			return (false);
	}
	return (true);
}

static bool	ft_match_middle(t_list **c, char **file, t_wc *wc, t_list **lst)
{
	size_t	len;
	t_list	*current;

	current = *c;
	if (current)
	{
		len = ft_strlen(current->content);
		if (!ft_strncmp(*file, current->content, len))
		{
			*file += len;
			*c = current->next;
			if (*c == NULL && !wc->end && !*file)
			{
				ft_putstr_fd("dans middle: ", 1);
				ft_putendl_fd(wc->str, 1);
				ft_lstadd_back(lst, ft_lstnew(ft_strdup(wc->str)));
				return (true);
			}
		}
		else
			*file += 1;
		return (true);
	}
	return (false);
}

static bool	ft_match_end(t_list **lst, t_wc *wc, char *str, char **file)
{
	size_t	len;
	size_t	file_len;

	file_len = ft_strlen(*file);
	if (wc->end)
	{
		len = ft_strlen(wc->end);
		if (file_len == len && !ft_strncmp(*file, wc->end, len))
		{
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(str)));
			return (true);
		}
		else
			*file += 1;
	}
	else
	{
	//	ft_putstr_fd("end str: ", 1);
	//	ft_putendl_fd(*file + 1, 1);
	//	if (*(*file + 1) != '\0')
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(str)));
		return (true);
	}
	return (false);
}

static void	ft_match_tempalte(t_wc *wc, t_list **lst, char *str)
{
	t_list	*current;
	char	*file;

	wc->str = str;
	current = wc->middle;
	file = str;
	if (((wc->start && ft_strncmp(wc->start, ".", 1)) || !wc->start)
		&& !ft_strncmp(str, ".", 1))
		return ;
	while (*file)
	{
		if (!ft_match_start(wc, str, &file))
			return ;
		if (ft_match_middle(&current, &file, wc, lst))
			continue ;
		if (ft_match_end(lst, wc, str, &file))
			return ;
	}
	return ;
}

t_list	*ft_listdir(t_wc *wc)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*current;
	t_list			*lst;

	pwd = getcwd(NULL, 1024);
	dir = opendir(pwd);
	current = readdir(dir);
	lst = NULL;
	while (current)
	{
		ft_match_tempalte(wc, &lst, current->d_name);
		current = readdir(dir);
	}
	closedir(dir);
	free(pwd);
	ft_sortwc(&lst);
	ft_free_wc(wc);
	return (lst);
}
