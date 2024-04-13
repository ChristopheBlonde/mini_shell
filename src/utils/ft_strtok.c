/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:56:02 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/13 15:01:38 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_arrcpy(char ***arr, char **new_arr, size_t *i)
{
	while ((*arr)[*i])
	{
		new_arr[*i] = ft_strdup((*arr)[*i]);
		if (!new_arr[*i])
		{
			ft_free_array(*(void **)new_arr);
			return ;
		}
		*i += 1;
	}
}

static void	ft_tokcpy(char ***arr, char *str, size_t n)
{
	char	**new_arr;
	size_t	arr_len;
	size_t	i;

	i = 0;
	arr_len = ft_arrlen(*(void **)arr);
	new_arr = (char **)ft_calloc(arr_len + 2, sizeof(char *));
	if (!new_arr)
		return ;
	ft_arrcpy(arr, new_arr, &i);
	new_arr[i] = (char *)ft_calloc(n + 1, sizeof(char));
	if (!new_arr[i])
	{
		ft_free_array((void **)new_arr);
		return ;
	}
	ft_memcpy((void *)new_arr[i], (void *)str, n);
	ft_free_array(*(void **)arr);
	*arr = new_arr;
}

static void	init_tok(t_tok *tok)
{
	tok->i = -1;
	tok->j = -1;
	tok->last = 0;
	tok->in_quotes = -1;
}

char	**ft_strtok(char *str, char *tok)
{
	char	**arr;
	t_tok	token;

	init_tok(&token);
	arr = (char **)ft_calloc(1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (str[++token.i])
	{
		token.j = -1;
		while (tok[++token.j])
		{
			in_quote(str, &token.in_quotes, token.i);
			if (token.i != 0 && str[token.i] == tok[token.j] \
				&& token.in_quotes == -1)
			{
				ft_tokcpy(&arr, &str[token.last], token.i - token.last);
				token.last = token.i;
				if (str[token.i + 1] == tok[token.j])
					token.i++;
			}
		}
	}
	return (arr);
}
