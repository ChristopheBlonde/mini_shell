/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:59:40 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/27 11:50:11 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	ft_check_end_of_file(char *tmp, char *line, char *limiter)
{
	size_t	i;
	char	*str;
	char	*delimiter;

	i = ft_strlen(line);
	delimiter = ft_strjoin(limiter, "\n");
	if (!delimiter)
		return (false);
	if (!ft_strncmp(delimiter, tmp, -1))
	{
		free(delimiter);
		return (true);
	}
	while (i > 0 && line[i - 1] != '\n')
		i--;
	str = ft_strjoin(&line[i], tmp);
	if (!str)
		return (false);
	if (!ft_strncmp(delimiter, str, -1))
	{
		ft_free_end_of_file(str, delimiter);
		return (true);
	}
	ft_free_end_of_file(str, delimiter);
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
	if (name)
		free(name);
	if (line)
		free(line);
	if (tmp)
		free(tmp);
	return (-1);
}

int	pre_check(int check, char c)
{
	if (check == 0 && c == '$')
		return (1);
	return (0);
}

void	ft_fork_heredoc(t_parse *parse, char *arr[3], int index)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror("minishell");
	if (pid == 0)
	{
		rl_catch_signals = 1;
		ft_sig_init(2);
		ft_handle_free_heredoc(parse, arr[1], arr[0]);
		ft_read_line(parse, arr[1], arr[2], index);
		free(arr[0]);
		ft_free_all(parse);
		exit(0);
	}
	waitpid(pid, &status, 0);
}
