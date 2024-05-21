/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/06 10:47:01 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_quote
{
	int		i;
	size_t	w_start;
	size_t	w_count;
	int		in_quotes;
	char	**result;
}	t_quote;

typedef struct s_tok
{
	int	i;
	int	j;
	int	last;
	int	in_quotes;
}	t_tok;

typedef struct s_wc
{
	char	*start;
	char	*end;
	char	*str;
	t_list	*middle;
	int		i;
	int		quote;
	size_t	len;
}	t_wc;

typedef struct s_env_handler
{
	char	*env;
	char	**new_env;
	int		new_env_len;
	int		var_end_size;
}	t_env_handler;

typedef	struct s_stuff
{
	int		z;
	int		k;
	char	*var;
}	t_stuff;

void	*ft_free_array(void **arr);
size_t	ft_arrlen(void **env);
char	**ft_strtok(char *str, char *tok);
size_t	ft_get_random(size_t max);
char	*ft_rand_str(size_t size);
int		ft_open_tmp(char **name);
int		ft_here_doc(t_parse *parse, int index);
bool	ft_check_end_of_file(char *tmp, char *line, char *limiter);
void	ft_error_heredoc(int n, char *limiter);
int		ft_fail_open(char *name, char *line, char *tmp);
void	ft_delete_quotes(t_parse *parse);
bool	ft_quoted(char *str);
void	ft_free_file_descriptor(void *ptr);
void	ft_free_arrstruct(void **arr, void (*f)(void *));
void	ft_free_all(t_parse *parse);
void	ft_listdir(void);
void	skip_spaces(char *input, int *i);
bool	check_if_dollar(char *str);
void	add_env_to_list(t_list **new_list, t_list *current,
	t_stuff *stuff, t_env_handler env_handler);
void	add_env_to_new_list(t_list **new_list, t_list *current,
	t_stuff *stuff, t_env_handler *e);
void	ft_env_handler(t_parse *parse);
void	ft_lstinsert(t_list **lst, t_list *addlst, t_list **ptr);
void	ft_lstto_arr(t_object **task, t_list *lst, int i);

#endif
