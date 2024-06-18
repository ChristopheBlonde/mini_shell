/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/18 10:52:54 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		ft_putstr_fd("\n", 1);
		exit(1);
	}
}

void	ft_sig_init(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, sig_handle_nothing);
		signal(SIGQUIT, sig_handle_nothing);
	}
	else if (mode == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, sig_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	sig_handle_nothing(int sig)
{
	(void)sig;
}
