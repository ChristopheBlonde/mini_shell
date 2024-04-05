/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/05 15:46:34 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	ft_usage(void)
{
	ft_putendl_fd("\033[1;34mUsage: [ minishell ]\033[m", 2);
	return (1);
}



int	main(int argc, char *argv[], char *env[])
{
	t_parse		parse;
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
	str = ft_get_next_line(0);
	if (!check_quote(str))
	{
		ft_putendl_fd("Error: unmatched quote", 2);
		free(str);
		return (1);
	}
	ft_parse_token(&parse, str);
	//str = ft_quote_handeler(str);
	free(str);
	//ft_objectify(&parse);
	//print_tokens(&parse);
	//print_objects(&parse);
	free_objects(&parse);
	ft_get_next_line(-42);
	ft_free_array((void **)parse.env);
	return (0);
}

