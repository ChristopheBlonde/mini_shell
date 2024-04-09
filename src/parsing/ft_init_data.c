/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:55:51 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/09 15:42:22 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data(t_parse *parse)
{
	parse->task = (t_object **)ft_calloc(1, sizeof(t_object *));
	parse->env = (char **)ft_calloc(1, sizeof(char *));
	parse->history = (char **)ft_calloc(1, sizeof(char *));
	parse->redirect = (t_file_descriptor **)ft_calloc(1,
			sizeof(t_file_descriptor *));
}
