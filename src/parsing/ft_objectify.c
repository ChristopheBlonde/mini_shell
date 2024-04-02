/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objectify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:04 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/02 17:00:35 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_link	ft_get_link(char *cmd)
{
	if (ft_strncmp(cmd, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(cmd, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(cmd, "|", 1) == 0)
		return (PIPE);
	return (NO_LINK);
}

static t_priority	ft_get_priority(char *cmd)
{
	if (ft_strncmp(cmd, "&&", 2) == 0 || ft_strncmp(cmd, "||", 2) == 0)
		return (MEDIUM);
	if (!ft_strncmp(cmd, ">", 1) || !ft_strncmp(cmd, ">>", 2)\
		|| !ft_strncmp(cmd, "<", 1) || !ft_strncmp(cmd, "<<", 2))
		return (HIGH);
	return (LOW);
}


/**
 * @brief Objectifies the parsed commands by setting the link, priority, infile, and outfile values for each task.
 *
 * This function iterates through the tasks in the parse structure and sets the link, priority, infile, and outfile values for each task.
 * The link value is obtained using the ft_get_link function, and the priority value is obtained using the ft_get_priority function.
 * If the link value is NO_LINK, the infile and outfile values are set to 0 and 1 respectively.
 * Otherwise, both infile and outfile values are set to 0.
 *
 * @param parse A pointer to the parse structure containing the parsed commands.
 */
void	ft_objectify(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		parse->task[i]->link = ft_get_link(parse->task[i]->cmd[0]);
		parse->task[i]->priority = ft_get_priority(parse->task[i]->cmd[0]);
	}
}


void	free_objects(t_parse *parse)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			free(parse->task[i]->cmd[j]);
			j++;
		}
		free(parse->task[i]->cmd);
		free(parse->task[i]);
		i++;
	}
	free(parse->task);
}

//TODO: Remplir le tebleau de redirection dans la structure parse

// static bool ft_is_redirect(char *cmd)
// {
// 	if (ft_strncmp(cmd, ">", 1) == 0 || ft_strncmp(cmd, ">>", 2) == 0 ||
// 		ft_strncmp(cmd, "<", 1) == 0 || ft_strncmp(cmd, "<<", 2) == 0)
// 		return (true);
// 	return (false);
// }


// static	t_file_operation ft_get_file_operation(char *cmd)
// {

// }

#include <stdio.h>
void	ft_fill_redirection(char **cmd, t_parse *parse)
{
	size_t	i;
	//size_t	j;
	//size_t	k;

	i = 0;
	//k = 0;
	(void)parse;
	while (cmd[i])
	{
		//j = 0;
		//printf("%s\n", cmd[i]);
		// while (cmd[i][j])
		// {
			if (cmd[i][0] == '>')
			{
			if (cmd[i][1] != '\0')
				ft_putendl_fd(cmd[i] + 1, 1);
				else
					ft_putendl_fd(cmd[i + 1], 1);
			}

		// 	{
		// 		ft_putendl_fd(cmd[i], 1);
		// 		ft_putendl_fd(cmd[i], 1);
		// 	}
		// 	// if (ft_is_redirect(cmd[i]))
		// 	// {
		// 	// 	// if faut Reallocation du tableau de redirection
		// 	// 	//parse->redirect[k] = ft_calloc(1, sizeof(t_file_descriptor));
		// 	// 	//parse->redirect[k]->type = ft_get_file_operation(cmd[i]);
		// 	// 	k++;
		// 	// }
		// 	j++;
		// }
		i++;
	}
}

