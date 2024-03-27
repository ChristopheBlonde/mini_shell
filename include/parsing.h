/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:35:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/27 09:36:54 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_parse
{
	char	***cmd;
	char	**env;
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

void	ft_parse_env(t_parse *parse, char *env[]);

#endif
