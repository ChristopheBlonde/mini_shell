/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/25 10:39:27 by cblonde          ###   ########.fr       */
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
	(void) argv;
	if (argc > 1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is not option !\n", 2);
		return (ft_usage());
	}
	ft_parse_env(env);
	return (0);
}
