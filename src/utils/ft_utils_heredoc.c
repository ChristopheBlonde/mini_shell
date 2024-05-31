/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:59:40 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/08 14:05:15 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	ft_check_end_of_file(char *tmp, char *line, char *limiter)
{
	size_t	i;
	char	*str;
	size_t	len;

	i = ft_strlen(line);
	len = ft_strlen(limiter);
	if (!ft_strncmp(limiter, tmp, len))
		return (true);
	while (i > 0 && line[i - 1] != '\n')
		i--;
	str = ft_strjoin(&line[i], tmp);
	if (!str)
		return (false);
	if (!ft_strncmp(limiter, str, len))
	{
		free(str);
		return (true);
	}
	free(str);
	return (false);
}

void	ft_error_heredoc(int n, char *limiter)
{
	if (n == 0)
	{
		ft_putstr_fd("\e[0;36mwarning: here-document\
 delimited by end-of-file (wanted `", 2);
		write(2, limiter, ft_strlen(limiter));
		ft_putendl_fd("')\e[0m", 2);
	}
	(void)limiter;
}

int	ft_fail_open(char *name, char *line, char *tmp)
{
	free(name);
	free(line);
	free(tmp);
	return (-1);
}
