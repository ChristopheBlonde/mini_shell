/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/12 09:20:49 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

static int	ft_usage(char **argv)
{
	if (argv[1])
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is not option !\n", 2);
	}
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
	if (parse->input == NULL)
	{
		printf("exit\n");
		ft_free_all(parse);
		exit(0);
	}
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

static bool	ft_initialize(int argc, char **argv, char **env, t_parse *parse)
{
	ft_sig_init(1);
	if (argc > 1)
	{
		ft_usage(argv);
		return (false);
	}
	ft_init_parse(parse);
	ft_parse_env(parse, env);
	if (!parse->env)
		return (false);
	ft_excmd_result(parse, 0);
	return (true);
}

int	main(int argc, char *argv[], char *env[])
{
	t_parse	parse;

	if (!ft_initialize(argc, argv, env, &parse))
		return (1);
	while (true)
	{
		if (g_exit_code != 0)
			ft_excmd_result(&parse, g_exit_code);
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
