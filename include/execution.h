/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:48:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/02 13:02:32 by cblonde          ###   ########.fr       */
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

#endif
