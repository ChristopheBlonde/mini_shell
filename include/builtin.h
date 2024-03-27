/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:43:25 by tsadouk           #+#    #+#             */
/*   Updated: 2024/03/27 13:14:00 by cblonde          ###   ########.fr       */
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

/*			UTILS			*/
int		ft_get_index_env(char **arr, char *var, int arr_len);

#endif
