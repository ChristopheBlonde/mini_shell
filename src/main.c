/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:21:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/22 16:58:55 by tsadouk          ###   ########.fr       */
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
        "command1 || command2",             // Correct
        "command1 | command2",              // Correct
        "command1 |& command2",             // Incorrect
        "command1 |&",                      // Incorrect
        "command1 &| command2",             // Incorrect
        "command1 &|",                      // Incorrect
        "command1 ||",                      // Incorrect
        "command1 ||| command2",            // Incorrect
        "command1 ||& command2",            // Incorrect
        "command1 &|& command2",            // Incorrect
        // Ajoutez ici plus de tests corrects et incorrects selon vos besoins
        NULL // Marqueur de fin de liste
    };

    for (int i = 0; tests[i] != NULL; ++i)
    {
        printf("Test #%d: %s\n", i + 1, tests[i]);
        if (ft_syntax_errors_handler(tests[i]) == 0)
        {
            printf("  Résultat: Correct\n");
        }
        else
        {
            printf("  Résultat: Incorrect\n");
        }
    }

    // Tests supplémentaires
    char *additional_tests[] = {
        "command1 | | command2",          // Incorrect: Opérateur '|' répété
        "command1 || | command2",         // Incorrect: Opérateur '|' après '||'
        "command1 ||&",                   // Incorrect: Opérateur '||' suivi de '&'
        "command1 |& | command2",         // Incorrect: Opérateur '|&' répété
        "command1 &|& | command2",        // Incorrect: Opérateur '&|&' répété
        "command1 | command2 | command3", // Incorrect: Opérateur '|' répété
        "command1 |&| command2",          // Incorrect: Opérateur '|&|' inattendu
        "command1 | command2 &",          // Incorrect: Opérateur '&' après '|'
        "command1 &| command2 &",         // Incorrect: Opérateur '&' répété
        "command1 &| | command2",         // Incorrect: Opérateur '&' suivi de '|'
        "command1 ||& command2 ||",       // Incorrect: Opérateur '||&' suivi de '||'
        "command1 |& command2 |",         // Incorrect: Opérateur '|&' suivi de '|'
        "command1 |&|& command2",         // Incorrect: Opérateur '|&' répété
        "command1 ||&| command2",         // Incorrect: Opérateur '||&|' inattendu
        "command1 || & command2",         // Incorrect: Opérateur '||' suivi de '&'
        "command1 && command2 |&",        // Incorrect: Opérateur '&&' suivi de '|&'
        "command1 |||& command2",         // Incorrect: Opérateur '|||&' inattendu
        NULL // Marqueur de fin de liste
    };

    for (int i = 0; additional_tests[i] != NULL; ++i)
    {
        printf("Test supplémentaire #%d: %s\n", i + 1, additional_tests[i]);
        if (ft_syntax_errors_handler(additional_tests[i]) == 0)
        {
            printf("  Résultat: Correct\n");
        }
        else
        {
            printf("  Résultat: Incorrect\n");
        }
    }

    return 0;
}
