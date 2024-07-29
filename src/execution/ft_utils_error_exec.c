/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_error_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:20:26 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/29 17:24:40 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_dot(t_parse *parse)
{
	print_good_error_msg(13);
	ft_free_all(parse);
	ft_close_std_fd();
	exit(2);
}
