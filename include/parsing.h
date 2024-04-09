/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:35:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/09 10:12:03 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

struct s_object;
struct s_file_descriptor;

typedef enum e_file_operation
{
	NO_OP,   
	READ,    
	WRITE,   
	APPEND,  
	HEREDOC  
}	t_file_operation;

typedef struct s_parse
{
	struct s_object				**task;
	char						**env;
	char						**history;
	struct s_file_descriptor	**redirect;
}	t_parse;

typedef struct	s_file_descriptor
{
	char	*file;
	bool	in_quote;
	int		fd;                   
	t_file_operation type;    
}	t_file_descriptor;

typedef enum e_link
{	
	NO_LINK,  
	PIPE,     
	OR,       
	AND,      
}	t_link;

typedef enum e_priority
{
	LOW,      
	MEDIUM,   
	HIGH,     
}	t_priority;

typedef struct s_object
{
	char	**cmd;          
	int		infile;         
	int		outfile;        
	t_link	link;           
	t_priority	priority;   
}	t_object;

void	ft_parse_env(t_parse *parse, char *env[]);
void	ft_parse_token(t_parse *parse, char *input);
void	print_tokens(t_parse *parse);
void	print_objects(t_parse *parse);
void	ft_objectify(t_parse *parse);
void	free_objects(t_parse *parse);
void	ft_fill_redirection(char **cmd, t_parse *parse);
void	print_cmd(t_parse *parse);
void	print_redirection_tab(t_parse *parse);

bool	check_quote(char *str);
char	*ft_quote_handeler(char *cmd);
char	*ft_strjoin_char(char *s, char c);
char **ft_split_with_quotes2(const char *str, char delimiter);
int is_in_quote(const char *str, size_t index, int in_quotes);
void copy_word(const char *str, size_t start, size_t end, char **result, size_t *word_count);

#endif

