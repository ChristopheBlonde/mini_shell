/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/22 11:00:49 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
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
void	ft_delete_quotes(t_parse *parse, size_t i);
void	ft_free_file_descriptor(void *ptr);
void	ft_free_arrstruct(void **arr, void (*f)(void *));
void	ft_free_all(t_parse *parse);

#endif
