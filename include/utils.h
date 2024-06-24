/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/22 08:39:08 by cblonde          ###   ########.fr       */
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
# include <string.h>

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
void	skip_spaces(char *input, int *i);
void	ft_lstinsert(t_list **lst, t_list *addlst, t_list **ptr);
void	ft_lstto_arr(t_object *task, t_list *lst);
t_list	*ft_listdir(t_wc *wc);
t_wc	*ft_init_wc(void);
void	ft_unquote(t_wc *wc);
void	ft_free_wc(t_wc *wc);
void	ft_sortwc(t_list **lst);
void	ft_delete_quotes(t_parse *parse);
void	in_quote(char *input, int *quote, int i);
void	skip_spaces(char *input, int *i);
char	**ft_strsort_arr(char **arr);
t_list	*ft_suppdouble(t_list *lst);
char	*ft_replace_var(t_parse *parse, char *line, char *str, char *var);
int		pre_check(int check, char c);
void	ft_fork_heredoc(t_parse *parse, char *line, char *tmp, int index);
void	ft_read_line(t_parse *parse, char *line, char *tmp, int index);
void	ft_del_dollar(t_parse *parse);
void	ft_clean_dollar(t_parse *parse);
void	ft_handle_free_heredoc(t_parse *parse, char *line, char *tmp);

/*	SIGNAL	*/
void	sig_handler(int sig);
void	ft_sig_init(int mode);
void	sig_handle_nothing(int sig);
void	ft_sig_exit(int status);
void	sig_handler_heredoc(int sig);

#endif
