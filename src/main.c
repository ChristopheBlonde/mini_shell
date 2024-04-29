/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/29 15:08:38 by cblonde          ###   ########.fr       */
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
	t_parse	parse;
	char *str;

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
//	parse.redirect = (t_file_descriptor **)ft_calloc(2, sizeof(t_file_descriptor *));
//	if (!parse.redirect)
//		return (2);
//	parse.redirect[0] = (t_file_descriptor *)ft_calloc(1, sizeof(t_file_descriptor));
//	parse.redirect[0]->file = ft_strdup("end\n");
//	ft_init_term(&parse);
//	ft_init_attr();
//	ft_export(&parse, "TEST=good_test");
//	str = ft_getenv(&parse, "USER");
//	ft_putendl_fd(str, 1);
//	if (str)
//		free(str);
//	ft_putstr_fd("\033[1;35m", 1);
//	ft_env(&parse);
//	ft_putstr_fd("\033[m", 1);
	ft_listdir();
	str = ft_get_next_line(0);
	if (!check_quote(str))
	{
		ft_putendl_fd("Error: unmatched quote", 2);
		free(str);
		ft_get_next_line(-42);
		ft_free_array((void **)parse.env);
		return (1);
	}
	ft_parse_token(&parse, str);
	free(str);
//	ft_objectify(&parse);
	//print_tokens(&parse);
	//print_objects(&parse);
	ft_get_next_line(-42);
	ft_free_all(&parse);
//	ft_here_doc(&parse, 0);
//	free(parse.redirect[0]->file);
//	free(parse.redirect[0]);
//	free(parse.redirect);
	return (0);
}
