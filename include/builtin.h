/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:43:25 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/16 16:31:24 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/*			ECHO			*/
char	ft_echo(char *str);

/*			EXPORT			*/
void	ft_export(t_parse *parse, char *new);
void	ft_error_env(char *env);
void	ft_putexport(char **env);
void	ft_exec_export(t_parse *parse, t_object *task);
char	*ft_getkey_env(char *env);

/*			UNSET			*/
void	ft_unset(t_parse *parse, char *var);

/*			ENV				*/
void	ft_env(t_parse *parse);

/*			UTILS			*/
int		ft_get_index_env(char **arr, char *var, int arr_len);
char	*ft_getenv(t_parse *parse, char *var);
void	ft_builtin(t_parse *parse);

#endif
