/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:17:21 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/06 13:58:17 by tsadouk          ###   ########.fr       */
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

static void	copy_word(char *str, t_quote *q)
{
	size_t	word_length;

	word_length = q->i - q->w_start;
	q->result[q->w_count] = (char *)ft_calloc(word_length + 1, sizeof(char));
	if (!q->result[q->w_count])
		return ;
	ft_strlcpy(q->result[q->w_count], str + q->w_start, word_length + 1);
	q->w_count++;
}

char	**ft_split_with_quotes(char *str, char delimiter)
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
			copy_word(str, &q);
			if (!q.result[q.w_count - 1] && ft_free_array((void **)q.result))
				return (NULL);
		}
		if ((str[q.i] == delimiter || str[q.i] == '\n') && q.in_quotes == -1)
			q.w_start = q.i + 1;
	}
	if (q.i > (int)q.w_start)
		copy_word(str, &q);
	if (q.w_count != 0
		&& !q.result[q.w_count - 1] && ft_free_array((void **)q.result))
		return (NULL);
	return (q.result);
}




int new_size(char **cmd)
{
    int arr_len;
    int i;
    int j;

    arr_len = ft_arrlen((void **)cmd);
    i = 0;
    while (cmd[i])
    {
        j = 0;
        while (cmd[i][j])
        {
            if (cmd[i][j] == '>' || cmd[i][j] == '<')
            {
                arr_len++;
                if (cmd[i][j + 1] == '>' || cmd[i][j + 1] == '<')
                    j++;
                if (cmd[i][j + 1])
                    arr_len++;
            }
            j++;
        }
        i++;
    }
	//printf("new_size = %d\n", arr_len);
    return arr_len;
}

char	*ft_strndup(char *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)ft_calloc(n + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

// On va re split pour chaque redirection
// From cmd[0] = echo, cmd[1] = a>oui
// to cmd[0] = echo, cmd[1] = a, cmd[2] = >, cmd[3] = oui

void	free_new_cmd(char **new_cmd)
{
	int i;

	i = 0;
	while (new_cmd[i])
	{
		free(new_cmd[i]);
		i++;
	}
	free(new_cmd);
}

char	**new_split(char **cmd)
{
	char	**new_cmd;
	int		i;
	int		j;
	int		len;
	int 	index;

	index = 0;
	len = new_size(cmd);
	new_cmd = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!new_cmd)
		return (NULL) ;
	i = 0;
	while (cmd[i])
	{
		j = 0;
		
		if (strchr(cmd[i], '>') == NULL && strchr(cmd[i], '<') == NULL)
		{
			new_cmd[index] = ft_strdup(cmd[i]);
			if (!new_cmd[index])
			{
				free_new_cmd(new_cmd);
				return (NULL) ;
			}
			index++;
			i++;
			continue;
		}
		while (cmd[i][j])
		{
			if (cmd[i][j] == '>' || cmd[i][j] == '<')
			{
				new_cmd[index] = ft_strndup(cmd[i], j);
				if (!new_cmd[index])
				{
					free_new_cmd(new_cmd);
					return (NULL) ;
				}
				index++;
				if (cmd[i][j + 1] == '>' || cmd[i][j + 1] == '<')
				{
					new_cmd[index] = ft_strndup(&cmd[i][j], 2);
					if (!new_cmd[index])
					{
						free_new_cmd(new_cmd);
						return (NULL) ;
					}
					index++;
					j++;
				}
				else
				{
					new_cmd[index] = ft_strndup(&cmd[i][j], 1);
					if (!new_cmd[index])
					{
						free_new_cmd(new_cmd);
						return (NULL) ;
					}
					index++;
				}
				if (cmd[i][j + 1])
				{
					new_cmd[index] = ft_strdup(&cmd[i][j + 1]);
					if (!new_cmd[index])
					{
						free_new_cmd(new_cmd);
						return (NULL) ;
					}
					index++;
				}
			}
			j++;
		}
		i++;
	}
	// for (int k = 0; new_cmd[k]; k++)
	// 	printf("new_cmd[%d] = %s\n", k, new_cmd[k]);
	free_new_cmd(cmd);
	return (new_cmd);
}
