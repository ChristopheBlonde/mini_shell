/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambigous_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:57:20 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/30 09:26:17 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strnstr_and_check_quotes(char *input, char *str, int n)
{
	int	i;
	int	j;
	int	in_quotes;

	i = -1;
	in_quotes = -1;
	while (input[++i] && i < n)
	{
		j = 0;
		in_quote(input, &in_quotes, i);
		if (in_quotes != -1)
			continue ;
		while (str[j] && input[i + j] && i + j < n)
		{
			if (input[i + j] != str[j])
				break ;
			j++;
		}
		if (!str[j])
			return (1);
	}
	return (0);
}

static bool	is_next_token_good(char *input, int i, int my_case)
{
	int	tmp;

	tmp = 0;
	if (input[i + 1] && input[i + 1] == '>' && my_case == 1)
	{
		tmp = i + 2;
		skip_spaces(input, &tmp);
		if (input[tmp] == '>' || input[tmp] == '<')
			return (false);
	}
	if (input[i + 1] && input[i + 1] == '<' && my_case == 2)
	{
		tmp = i + 2;
		skip_spaces(input, &tmp);
		if (input[tmp] == '<' || input[tmp] == '>')
			return (false);
	}
	return (true);
}

static int	line_check(char *input)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = -1;
	while (input[++i])
	{
		in_quote(input, &in_quotes, i);
		if (in_quotes != -1)
			continue ;
		if (input[i] == '>')
		{
			if (!is_next_token_good(input, i, 1))
				return (8);
		}
		if (input[i] == '<')
		{
			if (!is_next_token_good(input, i, 2))
				return (10);
		}
	}
	return (0);
}

static int	utils_ambigous(char *input, int *code)
{
	int	i;
	int	quote;

	i = -1;
	quote = -1;
	while (input[++i])
	{
		in_quote(input, &quote, i);
		if (quote == -1 && (input[i] == '<' || input[i] == '>'))
		{
			while (input[i] == '<' || input[i] == '>')
				i++;
			skip_spaces(input, &i);
			if (input[i] == '<' || input[i] == '>')
			{
				*code = 8;
				return (1);
			}
		}
	}
	return (0);
}

void	check_for_ambigous_redirect(char *input, int *code)
{
	int	len;

	len = ft_strlen(input);
	if (utils_ambigous(input, code))
		return ;
	if (line_check(input))
		*code = line_check(input);
	else if (ft_strnstr_and_check_quotes(input, ">>>", len)
		|| ft_strnstr_and_check_quotes(input, "<<>", len)
		|| ft_strnstr_and_check_quotes(input, "<<>", len)
		|| ft_strnstr_and_check_quotes(input, "<>", len)
	)
		*code = 8;
	else if (ft_strnstr_and_check_quotes(input, "<<<<", len)
		|| ft_strnstr_and_check_quotes(input, ">><", len))
		*code = 10;
}
