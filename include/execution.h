/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:48:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/29 17:43:32 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

bool	ft_execution(t_parse *parse);
bool	ft_exec_redirect(t_parse *parse, int index);
void	ft_get_path(t_parse *parse);
bool	ft_exec(t_parse *parse, t_object *task, size_t i);
void	ft_exec_builtin(t_parse *parse, t_object *task);
bool	ft_is_fork(t_parse *parse, size_t i);
bool	handle_bad_fd(t_parse *parse, t_object *task, size_t index, int n);
void	ft_handle_error_exec(t_parse *parse, char *str);
bool	ft_is_subexec(t_parse *parse, pid_t *sub_lvl,
			size_t *cur_sub, size_t *i);
bool	ft_exec_cmd(t_parse *parse, size_t *i, size_t cur_sub);
bool	ft_exec_pipe(t_parse *parse, size_t *i);
bool	ft_exec_or(t_parse *parse, size_t *i);
bool	ft_exec_and(t_parse *parse, size_t *i);
bool	ft_parse_befor_exec(t_parse *parse, size_t i);
void	ft_exit_forks(t_parse *parse, size_t i, int status, size_t cur_sub);
void	ft_handle_exit_parent(t_parse *parse, t_object *task);
int		ft_and_sublvl(t_parse *parse, size_t *i);
int		ft_or_sublvl(t_parse *parse, size_t *i);
bool	ft_exec_while_pipe(t_parse *parse, size_t *i);
void	ft_exit_dot(t_parse *parse);

#endif
