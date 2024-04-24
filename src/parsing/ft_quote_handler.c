/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:17:21 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/24 15:58:10 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_quote(t_quote *quote)
{
	quote->i = -1;
	quote->w_count = 0;
	quote->w_start = 0;
	quote->in_quotes = -1;
	quote->result = NULL;
}

static int	is_in_quote(const char *str, size_t index, int in_quotes)
{
	if (str[index] == '"' || str[index] == '\'')
	{
		if (in_quotes == -1)
			return (index);
		else
			return (-1);
	}
	return (in_quotes);
}

static char	*copy_word(const char *str, size_t start, size_t end,
		size_t *word_count)
{
	size_t	word_length;
	char	*new_str;

	word_length = end - start;
	new_str = (char *)ft_calloc(word_length + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str + start, word_length + 1);
	(*word_count)++;
	return (new_str);
}

char	**ft_split_with_quotes(const char *str, char delimiter)
{
	t_quote	q;

	ft_init_quote(&q);
	q.result = (char **)ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	if (!q.result)
		return (NULL);
	while (str[++q.i])
	{
		q.in_quotes = is_in_quote(str, q.i, q.in_quotes);
		if ((str[q.i] == delimiter || str[q.i] == '\n')
			&& q.in_quotes == -1 && (int)q.w_start != q.i)
		{
			q.result[q.w_count] = copy_word(str, q.w_start, q.i, &q.w_count);
			if (!q.result[q.w_count - 1] && ft_free_array((void **)q.result))
				return (NULL);
		}
		if ((str[q.i] == delimiter || str[q.i] == '\n') && q.in_quotes == -1)
			q.w_start = q.i + 1;
	}
	if (q.i > (int)q.w_start)
		q.result[q.w_count] = copy_word(str, q.w_start, q.i, &q.w_count);
	if (q.w_count != 0
		&& !q.result[q.w_count - 1] && ft_free_array((void **)q.result))
		return (NULL);
	return (q.result);
}
