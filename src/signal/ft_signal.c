#include "minishell.h"

void    sig_handler(int sig)
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

void    sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		g_exit_code = 130;
		close(0);
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
}

void	sig_handle_nothing(int sig)
{
	(void)sig;
}

void	ft_sig_exit(int status)
{
	if (!WIFEXITED(status) && WTERMSIG(status) == SIGINT)
	{
		g_exit_code = 130;
		ft_putendl_fd("", 2);
	}
	else if (!WIFEXITED(status) && WTERMSIG(status) == SIGQUIT)
	{
		g_exit_code = 131;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
	else
		g_exit_code = WEXITSTATUS(status);
}
