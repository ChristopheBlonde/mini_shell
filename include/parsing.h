/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:35:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/02 11:31:45 by cblonde          ###   ########.fr       */
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
	char						*input;
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

typedef enum e_builtin
{
	NO_BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtin;

typedef struct s_object
{
	char		**cmd;
	int			is_quoted;
	int			infile;
	int			outfile;
	int			pipe[2];
	int			status;
	pid_t		pid;
	t_link		link;
	t_builtin	builtin;
	t_priority	priority;
}	t_object;

typedef struct s_cmd_lst
{
	t_list	*lst;
	t_list	*current;
	t_list	*current_tmp;
	int		i;
	int		nb_dollar;
}	t_cmd_lst;

int					ft_check_and_operator(char *input);
int					ft_check_parenthesis(char *input);
int					ft_check_or_operator(char *input);
void				ft_parse_env(t_parse *parse, char *env[]);
bool				ft_parse_token(t_parse *parse, char *input);
void				print_tokens(t_parse *parse);
void				print_objects(t_parse *parse);
void				ft_objectify(t_parse *parse);
void				ft_redirection(t_parse *parse);
void				print_cmd(t_parse *parse);
void				print_redirection_tab(t_parse *parse);
bool				check_quote(char *str);
bool				ft_quoted(char *str);
char				*ft_strqcpy(char *s);
char				**ft_split_with_quotes(char *str, char delimiter);
void				in_quote(char *input, int *quote, int i);
void				ft_redirect_task(t_object *task, char *input,
						size_t index);
char				**ft_reduce_cmd(t_parse *parse,
						t_object *task, size_t index);
t_file_operation	ft_redirect_type(t_parse *parse, char *file, size_t i);
void				ft_wildcard(t_parse *parse);
int					ft_syntax_errors_handler(char *input);
int					ft_check_and_operator(char *input);
int					ft_check_parenthesis(char *input);
int					ft_check_or_operator(char *input);
void				ft_free_parsing(t_parse *parse);
void				ft_init_parse(t_parse *parse);
bool				ft_init_tasks(t_parse *parse, char **arr);
void				ft_skip_envchar(t_list *current, int *i);
void				ft_init_cmd_lst(t_cmd_lst *s, t_object *task);
void				ft_cmd_quoted(t_parse *parse, t_object *task, t_cmd_lst *s);
bool				ft_is_heredoc(t_parse *parse, size_t i);

#endif
