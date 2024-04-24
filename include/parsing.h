/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:35:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/24 16:50:44 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

struct	s_object;
struct	s_file_descriptor;

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
	bool				in_quote;
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

void				ft_parse_env(t_parse *parse, char *env[]);
void				ft_parse_token(t_parse *parse, char *input);
void				print_tokens(t_parse *parse);
void				print_objects(t_parse *parse);
void				ft_objectify(t_parse *parse);
void				ft_redirection(t_parse *parse);
void				print_cmd(t_parse *parse);
void				print_redirection_tab(t_parse *parse);
bool				check_quote(char *str);
char				*ft_strqcpy(char *s);
char				**ft_split_with_quotes(const char *str, char delimiter);
void				in_quote(char *input, int *quote, int i);
void				ft_clean_task(t_object *task,
						size_t i_cmd, size_t i_redirect);
char				**ft_reduce_cmd(char **cmd, size_t index);
t_file_operation	ft_redirect_type(char *file);

#endif
