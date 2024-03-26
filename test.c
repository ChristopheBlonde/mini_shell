/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:42:22 by tsadouk           #+#    #+#             */
/*   Updated: 2024/03/25 14:16:23 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "lib/libft.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;

	i = 0;
	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i])
	{
		j = 0;
		while (little[j] && big[j + i] == little[j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

static void	putchar_fd(char c, int fd)
{
	if (!c || !fd)
		return ;
	write(fd, &c, 1);
}

static void put_str_fd(char *str, int fd)
{
	if (!str || !fd)
		return ;
	while (*str)
		putchar_fd(*str++, fd);
}



char	ft_echo(char *str)
{
	int	option;

	option = 0;
	if (str == NULL)
		return (1);
	while (ft_isspace(*str))
		str++;
	if (*str == '\0')
	{
		putchar_fd('\n', 1);
		return (0);
	}
	if (*str == '-' && *(str + 1) == 'n')
	{
		str += 2;
		option = 1;
		while (ft_isspace(*str))
			str++;
	}
	put_str_fd(str, 1);
	if (!option)
		putchar_fd('\n', 1);
	return (0);
}

int	main (void)
{
	char	*line;

	while (1)
	{
		line = readline(">> ");
		if (line == NULL)
			break ;
		else if (line[0] != '\0')
		{
			add_history(line);
			if (ft_strnstr(line, "echo", 4) != NULL)
				ft_echo(line + 5);
			else
				printf("command not found: %s\n", line);
		}
		free(line);
	}
	return (0);
}