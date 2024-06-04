
#include "minishell.h"

void	case_if_0(t_cmd_lst *s)
{
	s->nb_dollar = -1;
	s->current = s->current->next;
}

void	case_if_1(t_cmd_lst *s, t_object *task, size_t *k)
{
	task->unquoted[*k] = false;
	s->nb_dollar = 0;
}

void	case_if_2(t_cmd_lst *s, t_object *task, size_t *k)
{
	task->unquoted[*k] = true;
	s->nb_dollar = 0;
}
