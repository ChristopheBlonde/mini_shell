/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:43:25 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/18 11:11:23 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "errno.h"

/*			ECHO			*/
void	ft_exec_echo(t_parse *parse, t_object *task);

/*			EXPORT			*/
void	ft_exec_export(t_parse *parse, t_object *task);
void	ft_export(t_parse *parse, char *new);
void	ft_excmd_result(t_parse *parse, int n);
bool	ft_replace_env(t_parse *parse, char *new);
void	ft_putexport(char **env);
char	*ft_getkey_env(char *env);

/*			UNSET			*/
void	ft_exec_unset(t_parse *parse, t_object *task);

/*			ENV				*/
int		ft_env(t_parse *parse);

/* 			PWD 			*/
void	ft_pwd(t_parse *parse);

/*			CD				*/
void	ft_cd(t_parse *parse, t_object *task, char *path);

/*			EXIT 			*/
int		ft_exit(t_parse *parse, t_object *task);

/*			UTILS			*/
int		ft_get_index_env(char **arr, char *var, int arr_len);
char	*ft_getenv(t_parse *parse, char *var);
void	ft_builtin(t_parse *parse);
void	ft_check_builtin(t_object *task, char *cmd, size_t len);
bool	ft_syntax_env(char *env, size_t n);
void	ft_error_env(char *env, size_t n);

#endif
