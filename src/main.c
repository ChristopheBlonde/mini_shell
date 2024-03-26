/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/26 14:11:53 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_usage(void)
{
	ft_putendl_fd("\033[1;34mUsage: [ minishell ]\033[m", 2);
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	char	**arr_env;
	int		i;

	i = 0;
	(void) argv;
	if (argc > 1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is not option !\n", 2);
		return (ft_usage());
	}
	arr_env = ft_parse_env(env);
	if (!arr_env)
		return (1);
	while (arr_env[i])
	{
		ft_putendl_fd(arr_env[i], 1);
		i++;
	}
	return (0);
}
