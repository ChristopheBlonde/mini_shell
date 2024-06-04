
#include "minishell.h"

void	case_if_0(t_cmd_lst *s)
{
	s->nb_dollar = -1;
	s->current = s->current->next;
}

void	case_if_1_or_2(t_cmd_lst *s, t_object *task, size_t *k, int case_nb)
{
	if (case_nb == 1)
	{
			task->unquoted[*k] = false;
			s->nb_dollar = 0;
	}
	else
	{
			task->unquoted[*k] = true;
			s->nb_dollar = 0;
	}
}

void	handle_new_unquoted(t_cmd_lst s, t_object *task, size_t j, t_list *new_lst)
{
	bool	*new_unquoted;

	new_unquoted = (bool *)ft_calloc(s.i + ft_lstsize(new_lst), sizeof(bool));
	if (!new_unquoted)
		return ;
	while (task->unquoted[j])
	{
		new_unquoted[j] = task->unquoted[j];
		j--;
	}
	while (j < (s.i + (size_t)ft_lstsize(new_lst)))
		new_unquoted[j++] = true;
	free(task->unquoted);
	task->unquoted = new_unquoted;
}