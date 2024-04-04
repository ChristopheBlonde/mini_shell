/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:35:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/04 16:13:09 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_file_operation
{
	NO_OP,
	READ,
	WRITE,
	APPEND,
	HEREDOC
}	t_file_operation;

typedef struct s_parse
{
	struct s_object				**task;
	char						**env;
	char						**history;
	struct s_file_descriptor	**redirect;
}	t_parse;

typedef struct s_file_descriptor
{
	char				*file;
	int					fd;
	t_file_operation	type;
}	t_file_descriptor;

typedef enum e_link
{
	NO_LINK,
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
	char		**cmd;
	int			infile;
	int			outfile;
	t_link		link;
	t_priority	priority;
}	t_object;

/* env */
void	ft_parse_env(t_parse *parse, char *env[]);

/* token */
void	ft_parse_token(t_parse *parse, char *input);

#endif
