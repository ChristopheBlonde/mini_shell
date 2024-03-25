/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:09:05 by cblonde           #+#    #+#             */
/*   Updated: 2023/12/11 11:25:20 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_check_line(char *buffer, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
	{
		i++;
		while (line[i])
		{
			buffer[j] = line[i];
			i++;
			j++;
		}
		buffer[j] = '\0';
		line[i - j] = '\0';
		return (true);
	}
	return (false);
}

char	*ft_get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			readbytes;

	line = ft_calloc(1, 1);
	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (buffer && line)
	{
		line = ft_strfjoin(line, buffer, 1);
		if (ft_check_line(buffer, line))
			return (line);
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes < 1)
		{
			free(buffer);
			buffer = NULL;
			if (line[0] != '\0')
				return (line);
			free(line);
			return (NULL);
		}
		buffer[readbytes] = '\0';
	}
	return (NULL);
}
