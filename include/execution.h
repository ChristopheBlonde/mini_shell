/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:48:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/18 10:48:01 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

bool	ft_execution(t_parse *parse);
bool	ft_exec_redirect(t_parse *parse);
void	ft_get_path(t_parse *parse);
void	ft_exec(t_parse *parse, t_object *task, size_t i);
void	ft_exec_builtin(t_parse *parse, t_object *task);
bool	ft_is_fork(t_parse *parse, size_t i);
void	handle_bad_fd(t_parse *parse, t_object *task, size_t index);
void	ft_handle_error_exec(char *str);

#endif
