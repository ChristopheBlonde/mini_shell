/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/03/26 15:47:36 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

char	ft_echo(char *str)
{
	int	option;

	option = 0;
	if (str == NULL)
		return (1);
	while (ft_isspace(*str))
		str++;
	if (*str == '\0')
	{
		putchar_fd('\n', 1);
		return (0);
	}
	if (*str == '-' && *(str + 1) == 'n')
	{
		str += 2;
		option = 1;
		while (ft_isspace(*str))
			str++;
	}
	put_str_fd(str, 1);
	if (!option)
		putchar_fd('\n', 1);
	return (0);
}
