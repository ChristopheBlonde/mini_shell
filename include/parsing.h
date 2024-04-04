
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
	struct s_object		**task;         
	char				**env;          
	char				**history;      
	struct s_file_descriptor	**redirect; 
	
}	t_parse;

typedef struct	s_file_descriptor
{
	char *file_name;          
	int fd;                   
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

#endif

