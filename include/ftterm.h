/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftterm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:11:18 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/03 14:19:07 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTTERM_H
# define FTTERM_H

# include "minishell.h"
# include <curses.h>
# include <term.h>
# include <termios.h>

int	ft_init_term(t_parse *parse);
int	ft_init_attr(void);

#endif
