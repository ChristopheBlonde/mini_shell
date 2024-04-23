/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/23 10:02:23 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static inline int	ft_usage(void)
{
	ft_putendl_fd("\033[1;34mUsage: [ minishell ]\033[m", 2);
	return (1);
}

int main()
{
    char *tests[] = {
        "command1 \"quoted text\"",            // Correct: Chaîne entre guillemets
        "command2 'quoted text'",             // Correct: Chaîne entre apostrophes
        "command3 |& command4",               // Incorrect: Caractère |& inattendu
        "command5 &&& command6",              // Incorrect: Caractère &&& inattendu
        "command7 (subcommand",               // Incorrect: Parenthèse non fermée
        "command8 )subcommand",               // Incorrect: Parenthèse fermée non précédée d'une ouverture
        "command9 && command10 ||command11", // Correct: Combinaison d'opérateurs logiques
        "command12 \"quoted 'text'\"",        // Correct: Chaîne entre guillemets avec apostrophe à l'intérieur
        "command13 'quoted \"text\"'",        // Correct: Chaîne entre apostrophes avec guillemets à l'intérieur
        "command14 (subcommand)",             // Correct: Parenthèses utilisées pour regrouper une sous-commande
        NULL // Marqueur de fin de liste
    };

    for (int i = 0; tests[i] != NULL; ++i)
    {
        printf("Test #%d: %s\n", i + 1, tests[i]);
        if (ft_syntax_errors_handler(tests[i]) == 1)
			printf("  Résultat: Incorrect\n");
		else
        	printf("  Résultat: Correct\n");
    }

    return 0;
}
