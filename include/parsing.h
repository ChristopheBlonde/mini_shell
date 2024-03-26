/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:35:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/25 16:25:17 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_parse
{
	char	***cmd;
	t_list	*env;
	char	**history;
	char	**redirect;
}	t_parse;

typedef struct s_env
{
	char	*name;
	char	*value;
	char	*full_env;
}	t_env;

/* env */

char	**ft_parse_env(char *env[]);

#endif
