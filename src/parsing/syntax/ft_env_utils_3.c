/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:29:13 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/14 15:54:05 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quoted_dollars(t_list *current, int *check)
{
	char	*new_content;
	size_t	new_content_index;
	size_t	i;
	char	quote;

	new_content = ft_calloc(ft_strlen(current->content) + 1, sizeof(char));
	if (!new_content)
		return ;
	new_content_index = 0;
	i = -1;
	quote = '\0';
	while (((char *)current->content)[++i])
	{
		if (is_quote(((char *)current->content)[i]))
			update_quotes_status(current, i, &quote);
		if (((char *)current->content)[i] == '$' && quote == '\0')
			continue ;
		new_content[new_content_index++] = ((char *)current->content)[i];
	}
	free(current->content);
	current->content = new_content;
	*check = 1;
}

static t_list	*process_env_handler(t_list *current, t_parse *parse,
	int z, int *index)
{
	char	*var;
	t_list	*new;

	*index = z + 1;
	ft_skip_envchar(current, index);
	var = ft_substr(current->content, z + 1, (size_t)index - z - 1);
	if (var[ft_strlen(var) - 1] == '"' || var[ft_strlen(var) - 1] == '\'')
		var[ft_strlen(var) - 1] = '\0';
	new = get_new(var, parse, current, z);
	free(var);
	return (new);
}

static t_list	*process_dollars_and_envs(t_list *current, t_parse *parse,
	int random, int *arr)
{
	char	quote;

	quote = '\0';
	while (((char *)current->content)[++arr[0]])
	{
		arr[3] = 0;
		handle_quotes(current, arr[0], &quote);
		if ((((char *)current->content)[arr[0]] == '$'
			&& (bool)++random) || arr[3] == 1)
		{
			if (random != arr[2])
				continue ;
			if (ft_quoted(&((char *)current->content)[arr[0] + 1])
				&& quote == '\0')
			{
				remove_quoted_dollars(current, &arr[3]);
				continue ;
			}
			return (process_env_handler(current, parse, arr[0], &arr[1]));
		}
	}
	return (NULL);
}

t_list	*ft_list_to_add(t_list *current, t_parse *parse,
	int nb_dollar, int random)
{
	t_list	*new;
	int		arr[4];

	new = NULL;
	arr[2] = count_dollar(current->content) - nb_dollar + 1;
	arr[0] = -1;
	new = process_dollars_and_envs(current, parse, random, arr);
	return (new);
}
