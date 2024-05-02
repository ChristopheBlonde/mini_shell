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
		else if (args[i] == '*' && !in_quote)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	return pwd;
}

void	ft_listdir(void)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*current;

	pwd = ft_get_pwd();
	dir = opendir(pwd);
	current = readdir(dir);
	while (current)
	{
		ft_putendl_fd(current->d_name, 1);
		current = readdir(dir);
	}
	closedir(dir);
	free(pwd);
}

t_list	*ft_init_wildcad(char *str)
{
	t_list	*lst;

	return (lst);
}
