/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:58:31 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/12 17:34:42 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * @brief Gère les guillemets dans une chaîne de caractères.
 *
 * Cette fonction vérifie si un caractère dans une chaîne de caractères est une guillemet simple ('\'') ou une guillemet double ('"').
 * Si le caractère est une guillemet simple ou double, la fonction met à jour la valeur de la variable quote en fonction de l'état actuel.
 * Si la variable quote est initialisée à -1, cela signifie qu'aucun guillemet n'a été rencontré jusqu'à présent.
 * Si la variable quote est égale à l'indice i, cela signifie que le guillemet actuel est le même que le guillemet précédent et donc la variable quote est réinitialisée à -1.
 *
 * @param input La chaîne de caractères à analyser.
 * @param quote Un pointeur vers la variable qui stocke l'état des guillemets.
 * @param i L'indice du caractère actuel dans la chaîne de caractères.
 */
void in_quote(char *input, int *quote, int i)
{
	if (input[i] == '\'' || input[i] == '"')
	{
		if (*quote == -1)
			*quote = i;
		else if (input[i] == input[*quote])
			*quote = -1;
	}
}

static	int	ft_parenthesis_handler(char *input)
{
	int	check;
	int	quote;
	int	i;

	check = 0;
	quote = -1;
	i = -1;
	while (input[++i])
	{
		in_quote(input, &quote, i);
		if (input[i] == '(' && quote == -1)
			check++;
		if (input[i] == ')' && quote == -1)
		{
			if (check == 0)
				return ((int) ')');
			check--;
		}
	}
	if (check != 0)
		return ((int) '(');
	return (0);
}

void	ft_check_parenthesis(char *input)
{
	int		check;
	char	*tmp;

	tmp = ft_strdup(input);
	check = ft_parenthesis_handler(tmp);
	if (check == (int) '(')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
		free(tmp);
		exit(0);
	}
	if (check == (int) ')')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
		free(tmp);
		exit(0);
	}
	free(tmp);
}
