/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/23 09:45:44 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_usage(void)
{
	ft_putendl_fd("\033[1;34mUsage: [ minishell ]\033[m", 2);
	return (1);
}

static bool	ft_empty_input(t_parse *parse)
{
	int	i;

	i = -1;
	while (ft_isspace(parse->input[++i]))
		if (parse->input[i + 1] == '\n')
			return (false);
	return (true);
}

static bool	ft_input(t_parse *parse)
{
	parse->input = readline("minishell> ");
	if (!parse->input || parse->input[0] == '\0')
	{
		ft_free_parsing(parse);
		return (false);
	}
	add_history(parse->input);
	parse->input = ft_strfjoin(parse->input, "\n", 1);
	if (!parse->input || !ft_empty_input(parse))
	{
		ft_free_parsing(parse);
		return (false);
	}
	if (ft_syntax_errors_handler(parse->input))
	{
		ft_free_parsing(parse);
		return (false);
	}
	return (true);
}

int	main(int argc, char *argv[], char *env[])
{
	t_parse	parse;

	if (argc > 1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is not option !\n", 2);
		return (ft_usage());
	}
	ft_init_parse(&parse);
	ft_parse_env(&parse, env);
	if (!parse.env)
		return (1);
	while (true)
	{
		if (!ft_input(&parse))
			continue ;
		if (!ft_parse_token(&parse, parse.input))
		{
			ft_putendl_fd("Error: fail parsing !", 2);
			ft_free_parsing(&parse);
			continue ;
		}
		if (!ft_execution(&parse))
			break ;
		ft_free_parsing(&parse);
	}
	ft_free_all(&parse);
	return (0);
}
