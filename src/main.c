/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/28 17:13:35 by tsadouk          ###   ########.fr       */
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
	t_parse		parse;
	t_object	*object;
	char		*str;

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
/*
	ft_export(&parse, "TEST=good_test");
	str = ft_getenv(&parse, "USER");
	ft_putendl_fd(str, 1);
	if (str)
		free(str);
	ft_putstr_fd("\033[1;35m", 1);
	ft_env(&parse);
	ft_putstr_fd("\033[m", 1);
*/

	object = malloc(sizeof(t_object));





	str = ft_get_next_line(0);
	ft_parse_token(&parse, str);
	free(str);
	ft_get_next_line(-42);
	ft_free_array((void **)parse.env);
	return (0);
}
