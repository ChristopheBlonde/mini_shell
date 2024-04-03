/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:18:20 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/03 14:47:52 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftterm.h"

int	ft_init_term(t_parse *parse)
{
	char	*term;
	int		ret;

	term = ft_getenv(parse, "TERM");
	if (!term)
	{
		ft_putendl_fd("\e[0;31mTERM: isn't find in 'env'.\e[0m", 2);
		return (-1);
	}
	ft_putendl_fd(term, 1);
	ret = tgetent(NULL, term);
	if (ret == -1)
	{
		ft_putendl_fd("\e[0;31mTermcaps: no access database.\e[0m", 2);
		return (-1);
	}
	if (ret == 0)
	{
		ft_putendl_fd("\e[0;31mTermcaps: partial database.\e[0m", 2);
		return (-1);
	}
	free(term);
	ft_putendl_fd("\e[1;32mTercaps: database loaded.\e[0m", 1);
	return (1);
}
int	ft_init_attr(void)
{
	struct termios info;

	tcgetattr(0, &info);
	info.c_lflag &= ~ICANON;      /* disable canonical mode */
	info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
	info.c_cc[VTIME] = 0;         /* no timeout */
	tcsetattr(0, TCSANOW, &info); /* set immediately */
	ft_putendl_fd("attr changed", 1);
	return (1);
}

inline void	ft_move_cursor(void)
{
	char	*cm_cap;

	cm_cap = tgetstr("cm", NULL);
	ft_putendl_fd(cm_cap, 1);
	free(cm_cap);
}
