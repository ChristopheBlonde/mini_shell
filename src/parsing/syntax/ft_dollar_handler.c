/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:31:12 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/05 22:46:51 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int get_nb_of_user(char *cmd)
// {
// 	int i;
// 	int nb;

// 	i = -1;
// 	nb = 0;
// 	while (cmd[++i])
// 	{
// 		if (cmd[i] == '$' && cmd[i + 1] == 'U' && cmd[i + 2] == 'S'\
// 			&& cmd[i + 3] == 'E' && cmd[i + 4] == 'R')
// 			nb++;
// 	}
// 	return (nb);
// }

// static int is_user(char *cmd, int i)
// {
// 	if (cmd[i] == '$' && cmd[i + 1] == 'U' && cmd[i + 2] == 'S'\
// 		&& cmd[i + 3] == 'E' && cmd[i + 4] == 'R')
// 		return (1);
// 	return (0);
// }


// // Rendre la fonction dynamique pour n'importe quelle variable d'environnement
// void    ft_dollar_handler(t_parse *parse)
// {
// 	int     i;
// 	int     j;
// 	int     index;
// 	char    *env;
// 	char    *new_cmd;

// 	env = ft_getenv(parse, "USER");
// 	i = -1;
// 	index = 0;
// 	while (parse->task[++i])
// 	{
// 		j = -1;
// 		while (parse->task[i]->cmd[++j])
// 		{
// 			if (parse->task[i]->cmd[j][0] != '\"')
// 				continue ;
// 			new_cmd = (char *)malloc(sizeof(char) * (ft_strlen(parse->task[i]->cmd[j]) - (5 * get_nb_of_user(parse->task[i]->cmd[j])) + (get_nb_of_user(parse->task[i]->cmd[j]) * ft_strlen(env)) + 1));
// 			if (!new_cmd)
// 				return ;
// 			int k = -1;
// 			int l = -1;
// 			while (parse->task[i]->cmd[j][++k])
// 			{
// 				if (is_user(parse->task[i]->cmd[j], k))
// 				{
// 					while (env[++l])
// 						new_cmd[index++] = env[l];
// 					k += 4;
// 				}
// 				new_cmd[index++] = parse->task[i]->cmd[j][k];
// 			}
// 			new_cmd[index] = '\0';
// 			free(parse->task[i]->cmd[j]);
// 			parse->task[i]->cmd[j] = new_cmd;
// 		}
// 	}
// }

t_list	*cmd_to_list(t_parse *parse)
{
	t_list	*list = NULL;
	t_task	*current_task = parse->task;

	while (current_task)
	{
		if (current_task->cmd)
			ft_lstadd_back(&list, ft_lstnew(current_task->cmd));
		current_task = current_task->next;
	}
	return (list);
}

void	replace_variable(char **content, int start, int end, char *env)
{
	char	*new_cmd;
	
	new_cmd = (char *)malloc(sizeof(char) * (strlen(*content) - (end - start) + strlen(env) + 1));
	if (!new_cmd)
		return;
	int k = -1;
	int l = -1;
	while ((*content)[++k])
	{
		if (k == start)
		{
			while (env[++l])
				new_cmd[++k] = env[l];
			k += strlen(env);
		}
		new_cmd[k] = (*content)[k];
	}
	new_cmd[k] = '\0';
	free(*content);
	*content = new_cmd;
}



void    ft_dollar_handler(t_parse *parse)
{
	t_list	*list;
	int		in_quote;
	int		i;
	int		j;
	char	*new_cmd;
	char	*env;
	char	*var;

	list = cmd_to_list(parse);
	while (list)
	{
		in_quote = 0;
		i = -1;
		while (((char *)list->content)[++i])
		{
			if (((char *)list->content)[i] == '\"')
				in_quote = !in_quote;
			if (((char *)list->content)[i] == '$' && !in_quote)
			{
				j = i;
				while (((char *)list->content)[j] && (((char *)list->content)[j] != ' ' && ((char *)list->content)[j] != '\"'))
					j++;
				var = ft_substr((char *)list->content, i + 1, j - i - 1);
				env = ft_getenv(parse, var);
				if (env)
					replace_variable((char **)&list->content, i, j, env);
				free(var);
			}
		}
	list = list->next;
	}
}