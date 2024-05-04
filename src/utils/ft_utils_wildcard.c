
#include "minishell.h"

t_wc	*ft_init_wc(void)
{
	t_wc	*wc;

	wc = (t_wc *)ft_calloc(1, sizeof(t_wc));
	if (!wc)
		return (NULL);
	wc->start = NULL;
	wc->middle = NULL;
	wc->end	= NULL;
	wc->i = -1;
	wc->quote = -1;
	wc->len = 0;
	return (wc);
}

void	ft_free_wc(t_wc *wc)
{
	if (wc->start)
	{
		free(wc->start);
		wc->start = NULL;
	}
	if (wc->end)
	{
		free(wc->end);
		wc->end = NULL;
	}
	if (wc->middle)
		ft_lstclear(&wc->middle, free);
}

void	ft_unquote(t_wc *wc)
{
	t_list *current;

	current = wc->middle;
	if (wc->start && ft_quoted(wc->start))
		wc->start = ft_strqcpy(wc->start);
	if (wc->end && ft_quoted(wc->end))
		wc->end = ft_strqcpy(wc->end);
	while (current)
	{
		if (ft_quoted(current->content))
			current->content = ft_strqcpy(current->content);
		current = current->next;
	}
}

void	ft_print_wc(t_wc *wc)
{
	t_list	*current;

	current = wc->middle;
	ft_putstr_fd("start: ", 1);
	if (wc->start)
		ft_putendl_fd(wc->start, 1);
	else
		ft_putendl_fd("NULL", 1);
	while (current)
	{
		ft_putstr_fd("middle: ", 1);
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
	ft_putstr_fd("end: ", 1);
	if (wc->end)
		ft_putendl_fd(wc->end, 1);
	else
		ft_putendl_fd("NULL", 1);
}
