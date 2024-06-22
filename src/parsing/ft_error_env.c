/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:08:16 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/21 17:14:46 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_env(char *env)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(env, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
