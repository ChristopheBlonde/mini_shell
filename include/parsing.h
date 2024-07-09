/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:35:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/09 13:02:29 by cblonde          ###   ########.fr       */
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
	int					task;
}	t_file_descriptor;

typedef enum e_link
{
	NO_LINK,
	PIPE,
	OR,
	AND,
}	t_link;

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
	bool		*unquoted;
	int			infile;
	int			outfile;
	int			pipe[2];
	int			status;
	int			errinfile;
	int			erroutfile;
	size_t		lvl;
	pid_t		pid;
	t_link		link;
	t_builtin	builtin;
}	t_object;

typedef struct s_elem
{
	t_list	*lst;
	char	*env;
	int		quoted;
	size_t	var_len;
}	t_elem;

typedef struct s_handle_env
{
	t_list	*lst;
	t_list	*cur;
	int		cur_count;
	size_t	size;
	t_elem	*info;
}	t_he;

int					ft_check_and_operator(char *input);
int					ft_check_parenthesis(char *input);
int					ft_check_or_operator(char *input);
void				ft_parse_env(t_parse *parse, char *env[]);
bool				ft_parse_token(t_parse *parse, char *input);
void				ft_objectify(t_parse *parse);
void				ft_redirection(t_parse *parse);
bool				check_quote(char *str);
bool				ft_quoted(char *str);
char				*ft_strqcpy(char *s);
char				**ft_split_with_quotes(char *str, char delimiter);
void				in_quote(char *input, int *quote, int i);
void				ft_redirect_task(t_object *task, char *input,
						size_t index);
char				**ft_reduce_cmd(t_object *task);
t_file_operation	ft_redirect_type(char *file);
void				ft_wildcard(t_parse *parse, int i);
int					ft_syntax_errors_handler(t_parse *parse, char *input);
void				ft_free_parsing(t_parse *parse);
void				ft_init_parse(t_parse *parse);
bool				ft_init_tasks(t_parse *parse, char **arr);
bool				ft_check_envvar(t_parse *parse, t_object *task,
						size_t index);
void				ft_handle_env(t_parse *parse, int k);
void				ft_init_he(t_he *he, t_object *task);
void				ft_init_elem(t_elem *elem);
void				ft_get_variable(t_parse *parse, char *s, t_elem *elem);
size_t				ft_count_dollar(char *s);
void				ft_check_insertion(t_he *he, t_elem *elem);
void				ft_get_priority(t_parse *parse);
void				ft_clean_operator(t_object *task);
bool				need_split(char *cmd);
char				**new_split(char **cmd);
bool				ft_split_args(char *cmd, char **new_cmd, int *index);

#endif
