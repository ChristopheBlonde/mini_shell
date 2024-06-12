/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:29:13 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/12 15:56:49 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static void	remove_quoted_dollars(t_list *current, int *check)
{
	char	*new_content;
	size_t	new_content_index;
	size_t	i;
	char	quote;

	new_content = (char *)malloc(ft_strlen(current->content) + 1);
	if (!new_content)
		return ;
	new_content_index = 0;
	i = 0;
	quote = '\0';
	while (((char *)current->content)[i])
	{
		if (is_quote(((char *)current->content)[i]))
		{
			if (quote == '\0')
				quote = ((char *)current->content)[i];
			else if (quote == ((char *)current->content)[i])
				quote = '\0';
		}
		if (((char *)current->content)[i] == '$' && quote == '\0')
		{
			i++;
			continue ;
		}
		new_content[new_content_index++] = ((char *)current->content)[i];
		i++;
	}
	new_content[new_content_index] = '\0';
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
	new = get_new(var, parse, current, z);
	free(var);
	return (new);
}

t_list	*ft_list_to_add(t_list *current, t_parse *parse, int nb_dollar, int random)
{
	t_list	*new;
	int		arr[4];
	char	quote;

	arr[2] = count_dollar(current->content) - nb_dollar + 1;
	arr[0] = -1;
	new = NULL;
	quote = '\0';
	while (((char *)current->content)[++arr[0]])
	{
		arr[3] = 0;
		if (is_quote(((char *)current->content)[arr[0]]))
		{
			if (quote == '\0')
				quote = ((char *)current->content)[arr[0]];
			else if (quote == ((char *)current->content)[arr[0]])
				quote = '\0';
		}
		if (((char *)current->content)[arr[0]] == '$' && quote != '\0' && (bool)++random)
		{
			if (random != arr[2])
				continue;
			if (ft_quoted(&((char *)current->content)[arr[0] + 1]))
				
			{
				remove_quoted_dollars(current, &arr[3]);
				printf("Current content: %s\n", (char *)current->content);
			}
			if (arr[3] == 1)
			{
				current->content = ft_strqcpy((char *)current->content);
				continue;
			}
			new = process_env_handler(current, parse, arr[0], &arr[1]);
			break;
		}
	}
	return (new);
}
