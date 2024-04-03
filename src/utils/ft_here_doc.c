/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:13:03 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/03 09:21:50 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* check print prompt */
static void	ft_prompt(char *tmp, char *line)
{
	if (line && tmp && (line[0] == '\0' || line[ft_strlen(line) - 1] == '\n'))
		ft_putstr_fd("heredoc>", 1);
	free(tmp);
	tmp = NULL;
}
/* check end file */
/*static void	ft_check_end_of_file(tmp, line)
{

}*/
/* check variable */


/* init doc */
int	ft_here_doc(void)
{
	char	*tmp;
	char	*line;
	char	*name;
	int		fd;

	name = NULL;
	line = (char *)ft_calloc(1, sizeof(char));
	if (!line)
		return (-1);
	tmp = (char *)ft_calloc(1, sizeof(char));
	if (!tmp)
	{
		free(line);
		return (-1);
	}
	if (ft_open_tmp(name) < 0)
		return (-1);
	while (true)
	{
		ft_prompt(tmp, line);
		tmp = ft_get_next_line(0);
		//ft_check_end_of_file(tmp, line);
	}
	return (fd);
}
