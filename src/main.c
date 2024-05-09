/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/06 10:53:55 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_usage(void)
{
	ft_putendl_fd("\033[1;34mUsage: [ minishell ]\033[m", 2);
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	t_parse	parse;
	char *str;

	if (argc > 1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is not option !\n", 2);
		return (ft_usage());
	}
	ft_parse_env(&parse, env);
	if (!parse.env)
		return (1);
	while (true)
	{
		str = readline("minishell>");
		str = ft_strfjoin(str, "\n", 1);
		if (!str)
		{
			ft_free_all(&parse);
			return (1);
		}
		if (ft_syntax_errors_handler(str))
		{
			ft_free_parsing(&parse);
			free(str);
			continue ;
		}
		ft_parse_token(&parse, str);
		ft_free_parsing(&parse);
		if (!ft_strncmp(str, "exit", 4))
		{
			free(str);
			break ;
		}
		free(str);
	}
	ft_free_all(&parse);
	return (0);
}
