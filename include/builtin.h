/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:43:25 by tsadouk           #+#    #+#             */
/*   Updated: 2024/03/27 15:28:12 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/*			ECHO			*/
char	ft_echo(char *str);

/*			EXPORT			*/
void	ft_export(t_parse *parse, char *new);

/*			UNSET			*/
void	ft_unset(t_parse *parse, char *var);

/*			ENV				*/
void	ft_env(t_parse *parse);

/*			UTILS			*/
int		ft_get_index_env(char **arr, char *var, int arr_len);
char	*ft_getenv(t_parse *parse, char *var);

#endif
