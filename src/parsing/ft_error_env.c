/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:16 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/15 10:45:28 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_env(char *env, size_t n)
{
	if (n == 0)
		ft_putstr_fd("minishell: export: `", 2);
	if (n == 1)
		ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(env, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
