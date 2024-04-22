/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_operator_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:45:50 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/22 17:00:28 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	check_after_spaces_without_pipe(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == ';' \
		|| input[i] == '<' || input[i] == '>' || input[i] == '\n')
		return (1);
	return (0);
}

static int	check_after_spaces(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == '|' || input[i] == ';' \
		|| input[i] == '<' || input[i] == '>' || input[i] == '\n')
		return (1);
	return (0);
}

static	int ft_or_operator_handler(char *input)
{
	int	i;
	int	check;
	int	in_quotes;

	i = -1;
	in_quotes = -1;
	while (input[++i])
	{
		check = 0;
		in_quote(input, &in_quotes, i);
		if (input[i] == '|' && in_quotes == -1)
		{
			if (input[i + 1] == '\n')
				return (1);
			if (input[i + 1] == '|')
				check = 1;
			else
				check = 2;
			i += 2;
		}
		if (check == 1 && check_after_spaces(input, i))
			return (1);
		else if (check == 2 && check_after_spaces(input, i))
			return (1);
	}
	return (0);
}

int	ft_check_or_operator(char *input)
{
	int	check;

	check = ft_or_operator_handler(input);
	if (check != 0)
	{
		printf("Error: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

// int main()
// {
//     char *tests[] = {
//         "command1 || command2",             // Correct
//         "command1 | command2",              // Correct
//         "command1 |& command2",             // Incorrect
//         "command1 |&",                      // Incorrect
//         "command1 &| command2",             // Incorrect
//         "command1 &|",                      // Incorrect
//         "command1 ||",                      // Incorrect
//         "command1 ||| command2",            // Incorrect
//         "command1 ||& command2",            // Incorrect
//         "command1 &|& command2",            // Incorrect
//         // Ajoutez ici plus de tests corrects et incorrects selon vos besoins
//         NULL // Marqueur de fin de liste
//     };

//     for (int i = 0; tests[i] != NULL; ++i)
//     {
//         printf("Test #%d: %s\n", i + 1, tests[i]);
//         if (ft_or_operator_handler(tests[i]) == 0)
//         {
//             printf("  Résultat: Correct\n");
//         }
//         else
//         {
//             printf("  Résultat: Incorrect\n");
//         }
//     }

//     return 0;
// }