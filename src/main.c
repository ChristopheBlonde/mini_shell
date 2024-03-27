/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/27 13:00:27 by cblonde          ###   ########.fr       */
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
	t_parse	parse;
	int		i;

	i = 0;
	(void) argv;
	if (argc > 1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is not option !\n", 2);
		return (ft_usage());
	}
	ft_parse_env(&parse, env);
	if (!parse.env)
		return (1);
	ft_export(&parse, "TEST=good_test");
	ft_unset(&parse, "TEST");
	while (parse.env[i])
	{
		ft_putendl_fd(parse.env[i], 1);
		i++;
	}
	ft_free_array((void **)parse.env);
	return (0);
}
