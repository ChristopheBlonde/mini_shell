/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:35:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/28 15:50:41 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_parse
{
	char	***cmd;
	char	**env;
	char	**history;
	char	**redirect;
}	t_parse;

typedef enum e_link
{	
	PIPE,
	OR,
	AND,
}	t_link;

typedef enum e_priority
{
	LOW,
	MEDIUM,
	HIGH,
}	t_priority;

typedef struct s_object
{
	char	**cmd;
	int		infile;
	int		outfile;
	t_link	link;
	t_priority	priority;
}	t_object;

/* env */
void	ft_parse_env(t_parse *parse, char *env[]);

/* token */
void	ft_parse_token(t_parse *parse, char *input);

#endif
