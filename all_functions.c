static inline int	ft_usage(void)
{
	ft_putendl_fd("\033[1;34mUsage: [ minishell ]\033[m", 2);
	return (1);
}

static bool	ft_empty_input(t_parse *parse)
{
	int	i;

	i = -1;
	while (ft_isspace(parse->input[++i]))
		if (parse->input[i + 1] == '\n')
			return (false);
	return (true);
}

static bool	ft_input(t_parse *parse)
{
	parse->input = readline("minishell> ");
	if (parse->input == NULL)
	{
		printf("exit\n");
		ft_free_all(parse);
		exit(0);
	}

int	main(int argc, char *argv[], char *env[])
{
	t_parse	parse;

	ft_sig_init(1);
	if (argc > 1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is not option !\n", 2);
		return (ft_usage());
	}

int	ft_get_index_env(char **arr, char *var, int arr_len)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (i < arr_len)
	{
		if (!ft_isalnum(arr[i][len])
			&& !ft_strncmp(arr[i], var, len))
			return (i);
		i++;
	}

void	ft_exec_export(t_parse *parse, t_object *task)
{
	size_t	i;

	i = 1;
	if (task->builtin != EXPORT)
		return ;
	if (!task->cmd[i])
		ft_putexport(parse->env);
	while (task->cmd[i])
	{
		ft_export(parse, task->cmd[i]);
		i++;
	}

void	ft_env_trim(char *str)
{
	int		i;
	int		j;
	size_t	count;
	int		start;

	i = -1;
	j = 0;
	count = 0;
	start = 0;
	while (str[++i] != '=')
	{
		start++;
		j++;
	}

static int	ft_echo(t_parse *parse, t_object *task)
{
	int		i;
	int		option;
	char	*str;

	i = 1;
	option = 0;
	if (task->cmd[1] && task->cmd[1][0] != '\0'
		&& !ft_strncmp(task->cmd[1], "-n", ft_strlen(task->cmd[1])))
	{
		option = 1;
		i++;
	}

void	ft_exec_echo(t_parse *parse, t_object *task)
{
	if (task->builtin != ECHO)
		return ;
	if (!task->cmd)
		return ;
	ft_echo(parse, task);
}

static void	ft_handle_cd_error(t_parse *parse, char *path, char **pwd,
		char **n_path)
{
	free(*pwd);
	*pwd = NULL;
	ft_excmd_result(parse, 1);
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
	if (*n_path && ft_strncmp(*n_path, path, ft_strlen(*n_path)))
		free(*n_path);
}

void	ft_getcd_path(bool *modified, char **n_path, char **pwd, int *res)
{
	*modified = true;
	while (*n_path[0] == '/')
		*n_path += 1;
	*pwd = ft_strfjoin(*pwd, "/", 1);
	*n_path = ft_strfjoin(*pwd, *n_path, 0);
	*res = chdir(*n_path);
}

static void	ft_update_env(t_parse *parse, char *n_path,
		char *path, bool modified)
{
	char	*pwd;
	char	*result;

	if (modified)
		result = n_path;
	else
		result = path;
	pwd = ft_getenv(parse, "PWD");
	if (!ft_strncmp(result, pwd, ft_strlen(pwd)))
		return ;
	ft_export(parse, ft_strjoin("OLDPWD=", pwd));
	ft_export(parse, ft_strjoin("PWD=", result));
}

static bool	ft_error_cd(t_parse *parse, t_object *task, char *str)
{
	if (!str)
	{
		ft_excmd_result(parse, 1);
		return (true);
	}

void	ft_cd(t_parse *parse, t_object *task, char *path)
{
	char	*pwd;
	int		res;
	char	*n_path;
	bool	modified;

	n_path = path;
	pwd = getcwd(NULL, 1024);
	modified = false;
	if (ft_error_cd(parse, task, pwd))
		return ;
	if (n_path[0] != '/')
		ft_getcd_path(&modified, &n_path, &pwd, &res);
	else
		res = chdir(path);
	if (res)
		return (ft_handle_cd_error(parse, path, &pwd, &n_path));
	free(pwd);
	ft_update_env(parse, n_path, path, modified);
	if (modified)
		free(n_path);
	return (ft_excmd_result(parse, 0));
}

void	ft_pwd(t_parse *parse)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
	{
		ft_excmd_result(parse, 1);
		return ;
	}

void	ft_error_env(char *env)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(env, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	ft_putexport(char **env)
{
	char	**arr;
	int		i;
	size_t	j;

	i = -1;
	arr = ft_strsort_arr(env);
	if (!arr)
		return ;
	while (arr[++i])
	{
		if (arr[i][0] == '?' || (arr[i][0] == '_' && arr[i][1] == '='))
			continue ;
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			j++;
		ft_putstr_fd("declare -x ", 1);
		write(1, arr[i], j + 1);
		if (arr[i][j] == '=')
			ft_putstr_fd("\"", 1);
		ft_putstr_fd(&arr[i][j + 1], 1);
		if (arr[i][j] == '=')
			ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
	}

static bool	ft_replace_append(t_parse *parse, size_t i, char **name, char *new)
{
	if (new[ft_strlen(*name)] == '+')
	{
		parse->env[i] = ft_strfjoin(parse->env[i],
				&new[ft_strlen(*name) + 2], 1);
		if (!parse->env[i])
		{
			ft_putendl_fd("Error: export", 2);
			free(*name);
			return (false);
		}

bool	ft_replace_env(t_parse *parse, char *new)
{
	char	*name;
	size_t	i;
	size_t	len;

	i = 0;
	name = ft_getkey_env(new);
	if (!name)
		return (true);
	len = ft_strlen(name);
	while (parse->env[i])
	{
		if (!ft_strncmp(parse->env[i], name, len)
			&& !ft_isalnum(parse->env[i][len]))
		{
			if (ft_replace_append(parse, i, &name, new))
			{
				free(name);
				return (true);
			}

int	ft_env(t_parse *parse)
{
	size_t	i;

	i = 0;
	if (!parse->env)
	{
		ft_excmd_result(parse, 1);
		return (1);
	}

static void	ft_check_builtin(t_object *task, char *cmd, size_t len)
{
	if (!cmd)
		return ;
	if (!ft_strncmp(cmd, "echo", len) && len == 4)
		task->builtin = ECHO;
	else if (!ft_strncmp(cmd, "cd", len) && len == 2)
		task->builtin = CD;
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
		task->builtin = PWD;
	else if (!ft_strncmp(cmd, "export", len) && len == 6)
		task->builtin = EXPORT;
	else if (!ft_strncmp(cmd, "unset", len) && len == 5)
		task->builtin = UNSET;
	else if (!ft_strncmp(cmd, "env", len) && len == 3)
		task->builtin = ENV;
	else if (!ft_strncmp(cmd, "exit", len) && len == 4)
		task->builtin = EXIT;
	else
		task->builtin = NO_BUILTIN;
}

void	ft_builtin(t_parse *parse)
{
	size_t	i;
	size_t	len;
	char	*cmd;

	i = 0;
	while (parse->task[i])
	{
		if (parse->task[i]->cmd)
			cmd = parse->task[i]->cmd[0];
		if (cmd)
			len = ft_strlen(cmd);
		ft_check_builtin(parse->task[i], cmd, len);
		i++;
	}

static bool	ft_is_number(char *str)
{
	size_t		i;
	long long	n;
	int			s;

	i = 0;
	n = 0;
	s = 1;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9') && str[i] != '-' && str[i] != '+')
			return (false);
		if (str[i] == '-')
			s *= -1;
		else
			n = n * 10 + (str[i] - '0');
		if ((n > 922337203685477580 && str[i + 1])
			|| (n * s < -922337203685477580 && str[i + 1])
			|| (n * s == 922337203685477580 && str[i] && str[i + 1] > '7')
			|| (n * s == -922337203685477580 && str[i] && str[i + 1] > '8'))
			return (false);
		i++;
	}

static long long	ft_atol_exit(char *str)
{
	long long	nbr;
	int			sign;
	size_t		i;

	sign = 1;
	nbr = 0;
	i = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (str[i] == '-')
			sign = -1;
		while (str[i] == '-' || str[i] == '+')
			i++;
		if (nbr == 922337203685477580 && str[i] == '8')
			return (-1);
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}

static void	ft_get_exit_code(long long *nbr)
{
	if (*nbr < 0)
		*nbr = 256 + (*nbr % 256);
	else
		*nbr = *nbr % 256;
}

int	ft_exit(t_parse *parse, t_object *task)
{
	long long	nbr;

	nbr = 0;
	if (task->cmd[1] && task->cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ft_excmd_result(parse, 1);
		return (1);
	}

static bool	ft_cpy_env(t_parse *parse, char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		arr[i] = ft_strdup(parse->env[i]);
		if (!arr[i])
		{
			ft_free_array((void **)arr);
			return (false);
		}

static bool	ft_syntax_env(char *env)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(env[0]) && env[0] != '_')
	{
		ft_error_env(env);
		return (false);
	}

void	ft_add_env(char **arr, size_t index, char *new)
{
	char	*name;
	size_t	i;
	size_t	len;

	name = ft_getkey_env(new);
	len = ft_strlen(name);
	i = len;
	if (new[len] == '+')
	{
		while (new[i])
		{
			new[i] = new[i + 1];
			i++;
		}

void	ft_export(t_parse *parse, char *new)
{
	size_t	len;
	size_t	i;
	char	**arr;

	if (!ft_syntax_env(new))
		return (ft_excmd_result(parse, 1));
	len = ft_arrlen((void **)parse->env);
	i = len;
	if (ft_replace_env(parse, new))
		return (ft_excmd_result(parse, 0));
	arr = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!arr)
		return (ft_excmd_result(parse, 1));
	if (!ft_cpy_env(parse, arr, len))
		return (ft_excmd_result(parse, 1));
	ft_add_env(arr, i, new);
	if (!arr[i])
	{
		ft_free_array((void **)arr);
		return (ft_excmd_result(parse, 1));
	}

void	ft_excmd_result(t_parse *parse, int n)
{
	char	*env;
	size_t	i;
	char	**arr;
	size_t	len;

	env = ft_strfjoin(ft_strdup("?="), ft_itoa(n), 3);
	if (!env)
		return ;
	len = ft_arrlen((void **)parse->env);
	i = len;
	if (ft_replace_env(parse, env))
	{
		free(env);
		return ;
	}

static bool	ft_cpy_env(t_parse *parse, char **arr, int index)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (parse->env[i])
	{
		if (i != (size_t)index)
		{
			arr[j] = ft_strdup(parse->env[i]);
			if (!arr[j])
			{
				ft_free_array((void **)arr);
				return (false);
			}

static void	ft_unset(t_parse *parse, char *var)
{
	size_t	len;
	char	**arr;
	int		index;

	len = ft_arrlen((void **)parse->env);
	index = ft_get_index_env(parse->env, var, len);
	if (index < 0)
		return (ft_excmd_result(parse, 0));
	arr = (char **)ft_calloc(len, sizeof(char *));
	if (!arr)
		return (ft_excmd_result(parse, 1));
	if (!ft_cpy_env(parse, arr, index))
		return (ft_excmd_result(parse, 1));
	ft_free_array((void **)parse->env);
	parse->env = arr;
	ft_excmd_result(parse, 0);
}

void	ft_exec_unset(t_parse *parse, t_object *task)
{
	size_t	i;

	i = 1;
	if (task->builtin != UNSET)
		return ;
	if (!task->cmd || !task->cmd[i])
		return ;
	while (task->cmd[i])
	{
		ft_unset(parse, task->cmd[i]);
		i++;
	}

void	ft_init_parse(t_parse *parse)
{
	parse->task = NULL;
	parse->env = NULL;
	parse->redirect = NULL;
	parse->input = NULL;
}

static void	ft_init_task(t_object *task)
{
	task->unquoted = NULL;
	task->infile = -1;
	task->outfile = -1;
	task->is_quoted = 0;
	task->pipe[0] = -1;
	task->pipe[1] = -1;
	task->errinfile = 0;
	task->erroutfile = 0;
}

bool	ft_init_tasks(t_parse *parse, char **arr)
{
	size_t	i;
	size_t	len;

	i = -1;
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1,
			sizeof(t_object *));
	if (!parse->task)
		return (false);
	len = ft_arrlen((void **)arr);
	while (++i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		if (!parse->task[i])
			return (false);
		parse->task[i]->cmd = ft_split_with_quotes(arr[i], ' ');
		if (!parse->task[i]->cmd)
			return (false);
		ft_init_task(parse->task[i]);
	}

bool	check_quote(char *str)
{
	int	quote;
	int	i;

	i = -1;
	quote = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (quote == -1)
				quote = i;
			else if (str[i] == str[quote])
				quote = -1;
		}

void	ft_delete_quotes(t_parse *parse)
{
	size_t	j;
	int		i;

	i = -1;
	while (parse->task[++i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			if (parse->task[i]->unquoted[j] == true)
			{
				j++;
				continue ;
			}

void	in_quote(char *input, int *quote, int i)
{
	if (input[i] == '\'' || input[i] == '"')
	{
		if (*quote == -1)
			*quote = i;
		else if (input[i] == input[*quote])
			*quote = -1;
	}

bool	ft_quoted(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}

void	ft_parse_env(t_parse *parse, char *env[])
{
	char	**arr_env;
	size_t	len;

	len = 0;
	while (env[len])
		len++;
	if (len == 0)
	{
		arr_env = ft_build_env();
		if (!arr_env)
			return ;
	}

static t_link	ft_get_link(char *cmd)
{
	if (!ft_strncmp(cmd, "&&", 2))
		return (AND);
	if (!ft_strncmp(cmd, "||", 2))
		return (OR);
	if (!ft_strncmp(cmd, "|", 1))
		return (PIPE);
	return (NO_LINK);
}

static t_priority	ft_get_priority(char *cmd)
{
	if (!ft_strncmp(cmd, "&&", 2) || !ft_strncmp(cmd, "||", 2))
		return (MEDIUM);
	if (!ft_strncmp(cmd, ">", 1) || !ft_strncmp(cmd, ">>", 2)
		|| !ft_strncmp(cmd, "<", 1) || !ft_strncmp(cmd, "<<", 2))
		return (HIGH);
	return (LOW);
}

void	ft_objectify(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		parse->task[i]->link = ft_get_link(parse->task[i]->cmd[0]);
		parse->task[i]->priority = ft_get_priority(parse->task[i]->cmd[0]);
		i++;
	}

bool	ft_parse_token(t_parse *parse, char *input)
{
	char	**arr;

	arr = ft_strtok(input, "|&\n");
	if (!arr)
		return (false);
	if (!ft_init_tasks(parse, arr))
	{
		ft_free_array((void **)arr);
		return (false);
	}

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

bool	ft_redirect_end(t_parse *parse, size_t *i, size_t *j, size_t *k)
{
	while (parse->task[*i]->cmd[*j])
	{
		if (ft_redirect_type(parse->task[*i]->cmd[*j]) != NO_OP)
		{
			parse->redirect = ft_realloc_redirect(parse->redirect, *k);
			if (!parse->redirect)
			{
				ft_free_arrstruct((void **)parse->redirect,
					ft_free_file_descriptor);
				return (false);
			}

void	ft_redirection(t_parse *parse)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	parse->redirect = NULL;
	while (parse->task[i])
	{
		j = 0;
		if (!ft_redirect_end(parse, &i, &j, &k))
			return ;
		ft_reduce_cmd(parse, parse->task[i]);
		i++;
	}

t_file_operation	ft_redirect_type(char *file)
{
	size_t	file_len;

	file_len = ft_strlen(file);
	if (file_len >= 2 && !ft_strncmp(file, ">>", 2))
		return (APPEND);
	if (file_len >= 2 && !ft_strncmp(file, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(file, "<", 1))
		return (READ);
	if (!ft_strncmp(file, ">", 1))
		return (WRITE);
	return (NO_OP);
}

void	ft_redirect_task(t_object *task, char *input, size_t index)
{
	if (!ft_strncmp(input, ">>", 2))
		task->outfile = index;
	if (!ft_strncmp(input, "<<", 2))
		task->infile = index;
	if (!ft_strncmp(input, "<", 1))
		task->infile = index;
	if (!ft_strncmp(input, ">", 1))
		task->outfile = index;
}

static size_t	ft_check_redirect(char *str)
{
	t_file_operation	type;

	if (!str)
		return (0);
	type = ft_redirect_type(str);
	if (type == NO_OP)
		return (0);
	if (type == APPEND || type == HEREDOC)
	{
		if (str[2] == '\0')
			return (2);
		else
			return (1);
	}

static void	ft_rewrite(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j] == '|' || str[j] == '&')
		j++;
	while (str[j])
	{
		str[i] = str[j];
		i++;
		j++;
	}

static size_t	ft_check_link(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|' || str[0] == '&')
	{
		if (str[1] == '\0')
			return (1);
		if (str[1] == '|' || str[1] == '&')
		{
			if (str[2] == '\0')
				return (1);
		}

bool ft_check_envvar(t_parse *parse, t_object *task, size_t index)
{
	char *env;

	//ft_putendl_fd(task->cmd[index], 1);
	if (task->cmd[index] && task->cmd[index][0] == '$')
	{
		env = ft_getenv(parse, &task->cmd[index][1]);
		//ft_putendl_fd(env, 1);	
		if ((index == 0 || task->cmd[index - 1] == NULL) && env == NULL)
		{
			free(task->cmd[index]);
			task->cmd[index] = NULL;
			return (true);
		}

static void	ft_cmdcpy(t_parse *parse, char **n_cmd, t_object *task)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (task->cmd[++i])
	{
		if (ft_check_link(task->cmd[i]) == 2)
			ft_rewrite(task->cmd[i]);
		if (ft_check_redirect(task->cmd[i]) == 0
			&& ft_check_link(task->cmd[i]) == 0 
			&& !ft_check_envvar(parse, task, i))
			n_cmd[++j] = task->cmd[i];
		else if (ft_check_redirect(task->cmd[i]) == 1
			|| ft_check_link(task->cmd[i]) == 1)
			free(task->cmd[i]);
		else if (ft_check_redirect(task->cmd[i]) == 2)
		{
			free(task->cmd[i]);
			i++;
			free(task->cmd[i]);
		}

static bool	ft_check_wildcard(char *args)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '"')
		{
			if (quote == args[i])
				quote = '\0';
			else
				quote = args[i];
		}

static size_t	ft_getsize(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == quote)
				quote = '\0';
			else
				quote = str[i];
		}

else if (wc->quote == -1 && str[wc->i] == '*')
		{
			while (str[wc->i] == '*')
				wc->i++;
			wc->len = ft_getsize(&str[wc->i]);
			if (str[wc->i + wc->len] == '\0' && wc->len > 0)
				wc->end = ft_substr(str, wc->i, wc->len);
			else if (wc->len > 0)
				ft_lstadd_back(&wc->middle,
					ft_lstnew(ft_substr(str, wc->i, wc->len)));
			wc->i += wc->len - 1;
		}

void	ft_wildcard(t_parse *parse)
{
	size_t	i;
	t_list	*lst;

	lst = NULL;
	i = 0;
	while (parse->task[i])
	{
		lst = ft_cmd_to_list(parse->task[i]);
		ft_lstto_arr(parse->task[i], lst);
		i++;
	}

void	ft_process_env(t_object *task, t_parse *parse)
{
	t_list	*list;
	size_t	arr_len;

	list = NULL;
	arr_len = ft_arrlen((void **)task->cmd);
	task->unquoted = (bool *)ft_calloc(arr_len + 1, sizeof(bool));
	if (!task->unquoted)
		return ;
	list = ft_cmd_to_list_env(task, parse);
	if (list)
		ft_lstto_arr(task, list);
}

void	ft_env_handler(t_parse *parse)
{
	int		i;

	i = -1;
	while (parse->task[++i])
	{
		ft_process_env(parse->task[i], parse);
	}

int	count_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}

bool	check_if_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}

void	add_env_to_list(t_list **new_list, t_list *current,
	t_stuff *stuff, t_env_handler env_handler)
{
	if (stuff->k == 0)
	{
		ft_lstadd_back(new_list, ft_lstnew(ft_strfjoin(
					ft_substr((char *)current->content, 0, stuff->z),
					env_handler.new_env[stuff->k], 1)));
		return ;
	}

void	add_env_to_new_list(t_list **new_list, t_list *current,
	t_stuff *stuff, t_env_handler *e)
{
	char	*temp;

	temp = NULL;
	temp = ft_strfjoin(ft_substr((char *)current->content,
				0, stuff->z), e->new_env[0], 1);
	temp = ft_strfjoin(temp, ft_substr((char *)current->content,
				ft_strlen(stuff->var) + 1 + stuff->z, e->var_end_size), 3);
	ft_lstadd_back(new_list, ft_lstnew(temp));
}

void	prompt_errors_handler(char *input)
{
	if (ft_strlen(input) == 0)
		ft_putstr_fd("minishell: syntax error near\
unexpected token`newline'\n", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(input[0], 2);
		ft_putstr_fd("'\n", 2);
	}

static int	ft_parenthesis_handler(char *input)
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

int	ft_check_parenthesis(char *input)
{
	int	check;

	check = ft_parenthesis_handler(input);
	if (check == (int) '(')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
		return (1);
	}

void	skip_spaces(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' '
			|| (input[*i] >= 9 && input[*i] <= 13)))
		(*i)++;
}

static int	check_after_spaces(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == '|' || input[i] == ';'
		|| input[i] == '\0' || input[i] == '\n')
		return (1);
	return (0);
}

static int	ft_and_operator_handler(char *input)
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
		if (input[i] == '&' && in_quotes == -1)
		{
			if (input[i + 1] != '&')
				return (1);
			check++;
			i += 2;
		}

int	ft_check_and_operator(char *input)
{
	int	check;

	check = ft_and_operator_handler(input);
	if (check != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
		return (1);
	}

void	ft_init_cmd_lst(t_cmd_lst *s, t_object *task)
{
	s->nb_dollar = -1;
	s->i = 0;
	s->lst = NULL;
	while (task->cmd[s->i])
	{
		ft_lstadd_back(&s->lst, ft_lstnew(ft_strdup(task->cmd[s->i])));
		s->i += 1;
	}

void	ft_cmd_quoted(t_parse *parse, t_object *task, t_cmd_lst *s)
{
	char	*str;
	char	*var;

	var = NULL;
	if (((char *)s->current->content)[0] == '\'')
	{
		task->is_quoted = 1;
		s->current = s->current->next;
		return ;
	}

void	ft_skip_envchar(t_list *current, int *i)
{
	while (((char *)current->content)[*i] &&
		((char *)current->content)[*i - 1] != '?' &&
		((char *)current->content)[*i] != ' ' &&
		((char *)current->content)[*i] != '"' &&
		((char *)current->content)[*i] != '$' &&
		((char *)current->content)[*i] != '\'' &&
		((char *)current->content)[*i] != '\n')
		*i += 1;
}

int	ft_syntax_errors_handler(char *input)
{
	if (ft_check_and_operator(input) || ft_check_or_operator(input)
		||ft_check_parenthesis(input))
		return (1);
	if (!check_quote(input))
	{
		ft_putendl_fd("Error: unmatched quote", 2);
		return (1);
	}

static bool	case_if_0(t_cmd_lst *s)
{
	if (s->nb_dollar == 0)
	{
		s->nb_dollar = -1;
		s->current = s->current->next;
		return (true);
	}

static bool	case_if_1_or_2(t_cmd_lst *s, t_object *task, size_t *k)
{
	if (task->is_quoted == 1)
	{
		task->unquoted[*k] = false;
		s->nb_dollar = 0;
		return (true);
	}

else if (task->is_quoted == 2)
	{
		task->unquoted[*k] = true;
		s->nb_dollar = 0;
		return (true);
	}

static void	handle_new_unquoted(t_cmd_lst s, t_object *task, size_t j,
	t_list *new_lst)
{
	bool	*new_unquoted;

	new_unquoted = (bool *)ft_calloc(s.i + ft_lstsize(new_lst), sizeof(bool));
	if (!new_unquoted)
		return ;
	while (task->unquoted[j])
	{
		new_unquoted[j] = task->unquoted[j];
		j--;
	}

static void	process_nb_dollar(t_cmd_lst *s, t_object *task, t_parse *parse,
	size_t j)
{
	t_list	*new_lst;

	if (s->nb_dollar == -1)
		s->nb_dollar = count_dollar(s->current->content);
	if (s->nb_dollar > 0)
	{
		new_lst = ft_list_to_add(s->current, parse, s->nb_dollar, 0);
		handle_new_unquoted(*s, task, j, new_lst);
		ft_lstinsert(&s->lst, new_lst, &s->current);
		s->nb_dollar -= 1;
	}

static int	check_after_spaces_without_pipe(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == ';'
		|| input[i] == '<' || input[i] == '>' || input[i] == '\n'
		|| input[i] == '\0')
		return (1);
	return (0);
}

static int	check_after_spaces(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == '|' || input[i] == ';'
		|| input[i] == '\n' || input[i] == '\0')
		return (1);
	return (0);
}

static int	handle_or_operator(char *input, int i, int in_quotes)
{
	int	check;

	check = 0;
	if (input[i] == '|' && in_quotes == -1)
	{
		if (input[i + 1] == '\n' || input[i + 1] == '\0')
			return (1);
		if (input[i + 1] == '|')
			check = 1;
		else
			check = 2;
		i += 2;
	}

static int	ft_or_operator_handler(char *input)
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
		check = handle_or_operator(input, i, in_quotes);
		if (check == 1 && check_after_spaces_without_pipe(input, i + 1))
			return (1);
		else if (check == 2 && check_after_spaces(input, i + 1))
			return (1);
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

bool	ft_is_fork(t_parse *parse, size_t i)
{
	if (parse->task[i]->builtin != NO_BUILTIN)
	{
		if (parse->task[i]->builtin == ECHO || parse->task[i]->builtin == ENV)
			return (true);
		else if (parse->task[i + 1] && parse->task[i + 1]->link == PIPE)
			return (true);
		else
			return (false);
	}

void	ft_exec_builtin(t_parse *parse, t_object *task)
{
	if (task->builtin == ECHO)
		ft_exec_echo(parse, task);
	if (task->builtin == CD)
		ft_cd(parse, task, task->cmd[1]);
	if (task->builtin == PWD)
		ft_pwd(parse);
	if (task->builtin == EXPORT)
		ft_exec_export(parse, task);
	if (task->builtin == UNSET)
		ft_exec_unset(parse, task);
	if (task->builtin == ENV)
		ft_env(parse);
	if (task->builtin == EXIT)
		ft_exit(parse, task);
}

static int	ft_check_if_exist(t_parse *parse, char *file, int index)
{
	size_t	i;

	i = 0;
	while (parse->redirect[i])
	{
		if ((int)i != index && !ft_strncmp(parse->redirect[i]->file, file, -1))
			return (i);
		i++;
	}

static void	handle_open(t_file_descriptor *file, t_parse *parse, int i)
{
	if ((file->type == WRITE || file->type == APPEND)
		&& parse->task[file->task]->erroutfile != 0)
		return ;
	if ( file->type == READ && parse->task[file->task]->errinfile != 0)
		return ;
	if (file->type == READ)
	{
		file->fd = open(file->file, O_RDONLY);
		parse->task[file->task]->erroutfile = errno;
	}

bool	ft_exec_redirect(t_parse *parse)
{
	size_t				i;
	t_file_descriptor	*file;
	int					exist;

	i = 0;
	if (!parse->redirect)
		return (true);
	while (parse->redirect[i])
	{
		file = (t_file_descriptor *)parse->redirect[i];
		exist = ft_check_if_exist(parse, file->file, i);
		if (exist != -1 && exist < (int)i
			&& file->type != parse->redirect[exist]->type)
			close(parse->redirect[exist]->fd);
		handle_open(file, parse, i);
		i++;
	}

static void	ft_close_fds(t_parse *parse, size_t index)
{
	size_t	i;

	i = 0;
	while (parse->redirect && parse->redirect[i])
	{
		if (parse->redirect[i]->fd != -1)
		{
			close(parse->redirect[i]->fd);
		}

static void	ft_handle_child(t_parse *parse, t_object *task, size_t i)
{
	if (task->infile != -1)
		dup2(parse->redirect[task->infile]->fd, 0);
	else if (task->link == PIPE)
		dup2(parse->task[i - 1]->pipe[0], 0);
	if ((!parse->task[i + 1] || parse->task[i + 1]->link != PIPE)
		|| parse->task[i]->builtin == ECHO)
	{
		if (task->outfile != -1)
			dup2(parse->redirect[task->outfile]->fd, 1);
	}

static void	ft_handle_parent(t_parse *parse, t_object *task, size_t i)
{
	close(task->pipe[1]);
	if (task->link == PIPE)
		close(parse->task[i - 1]->pipe[0]);
	if (!parse->task[i + 1] || parse->task[i + 1]->link != PIPE)
	{
		close(task->pipe[0]);
		waitpid(task->pid, &task->status, 0);
		if (WIFEXITED(task->status))
			ft_excmd_result(parse, WEXITSTATUS(task->status));
		if (WIFSIGNALED(task->status))
			ft_excmd_result(parse, WTERMSIG(task->status));
		if (WIFSTOPPED(task->status))
			ft_excmd_result(parse, WSTOPSIG(task->status));
		if (WIFCONTINUED(task->status))
		{
			ft_excmd_result(parse, 0);
		}

static void	ft_handle_status(t_parse *parse, t_object *task)
{
	int	status;

	status = 0;
	if (!task->cmd || !task->cmd[0])
	{
		exit(127);
	}

void	ft_exec(t_parse *parse, t_object *task, size_t i)
{
	pipe(task->pipe);
	task->pid = fork();
	if (task->pid < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}

static void	ft_exec_pipe(t_parse *parse, size_t *i)
{
	if (parse->task[*i] && parse->task[*i]->link != OR
		&& parse->task[*i]->link != AND)
	{
		ft_exec(parse, parse->task[*i], *i);
		*i += 1;
		while (parse->task[*i] && parse->task[*i]->link == PIPE)
		{
			ft_exec(parse, parse->task[*i], *i);
			*i += 1;
		}

static bool	ft_exec_or(t_parse *parse, size_t *i)
{
	if (parse->task[*i] && parse->task[*i]->link == OR)
	{
		if (parse->task[*i - 1]->status > 0)
		{
			ft_exec(parse, parse->task[*i], *i);
			*i += 1;
			while (parse->task[*i] && parse->task[*i]->link == PIPE)
			{
				ft_exec(parse, parse->task[*i], *i);
				*i += 1;
			}

static bool	ft_exec_and(t_parse *parse, size_t *i)
{
	if (parse->task[*i] && parse->task[*i]->link == AND)
	{
		if (parse->task[*i - 1]->status == 0)
		{
			ft_exec(parse, parse->task[*i], *i);
			*i += 1;
			while (parse->task[*i] && parse->task[*i]->link == PIPE)
			{
				ft_exec(parse, parse->task[*i], *i);
				*i += 1;
			}

void	ft_wait_all(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		waitpid(parse->task[i]->pid, &parse->task[i]->status, 0);
		i++;
	}

bool	ft_execution(t_parse *parse)
{
	size_t	i;

	i = 0;
	ft_exec_redirect(parse);
	ft_get_path(parse);
	ft_sig_init(0);
	while (parse->task && parse->task[i])
	{
		if (!ft_is_fork(parse, i))
			ft_exec_builtin(parse, parse->task[i++]);
		else
		{
			if (parse->task[i] && parse->task[i]->cmd && parse->task[i]->cmd[0])
			{
				ft_exec_pipe(parse, &i);
				if (!ft_exec_or(parse, &i))
					break ;
				if (ft_exec_and(parse, &i))
					break ;
			}

static void	put_error_msg(t_file_descriptor *file, size_t n)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(n), 2);
}

void	handle_bad_fd(t_parse *parse, t_object *task, size_t j)
{
	if (task->infile != -1)
	{
		int i = 0;
		while (parse->redirect[i])
		{
			if (parse->redirect[i]->task == (int)j && parse->redirect[i]->type == READ)
			{
				if (parse->redirect[i]->fd == -1)
				{
					put_error_msg(parse->redirect[i], task->errinfile);
					ft_free_all(parse);
					exit(1);
				}

static bool	ft_abs_path(char *path)
{
	int	res;

	res = access(path, X_OK);
	if (res == 0)
		return (true);
	return (false);
}

static void	ft_replace_path(t_object *task, char **paths)
{
	char	*path;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (task->cmd[j] && task->cmd[j][0] == '$')
		j++;
	if (!task || !task->cmd || !task->cmd[j])
		return ;
	if (ft_abs_path(task->cmd[j]))
		return ;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], task->cmd[j]);
		if (!path)
			continue ;
		if (!access(path, X_OK))
		{
			free(task->cmd[j]);
			task->cmd[j] = path;
		}

void	ft_get_path(t_parse *parse)
{
	char	**paths;
	int		i;

	i = -1;
	if (!parse->task)
		return ;
	paths = ft_get_env_path(parse);
	if (!paths)
		return ;
	while (parse->task[++i])
	{
		if (parse->task[i]->builtin == NO_BUILTIN)
			ft_replace_path(parse->task[i], paths);
	}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}

void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		g_exit_code = 130;
		close(0);
	}

void	ft_sig_init(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, sig_handle_nothing);
		signal(SIGQUIT, sig_handle_nothing);
	}

else if (mode == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}

void	sig_handle_nothing(int sig)
{
	(void)sig;
}

void	ft_sig_exit(int status)
{
	if (!WIFEXITED(status) && WTERMSIG(status) == SIGINT)
	{
		g_exit_code = 130;
		ft_putendl_fd("", 2);
	}

static void	ft_swap_strarr(char **arr, int i, int j)
{
	char	*tmp;

	tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

size_t	ft_get_random(size_t max)
{
	int		fd;
	size_t	count;
	char	buffer[250];
	size_t	i;

	i = 0;
	count = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("\033[0;31mFail open file random\033[m", 2);
		return (0);
	}

void	ft_free_file_descriptor(void *ptr)
{
	t_file_descriptor	*fd;

	fd = (t_file_descriptor *)ptr;
	if (fd->fd != -1)
		close(fd->fd);
	if (fd->file)
	{
		if (!ft_strncmp(fd->file, ".tfs", 4))
			unlink(fd->file);
		free(fd->file);
		fd->file = NULL;
	}

void	ft_free_redirect(t_parse *parse)
{
	ft_free_arrstruct((void **)parse->redirect, ft_free_file_descriptor);
}

void	ft_free_task(t_parse *parse)
{
	int	i;

	i = -1;
	while (parse->task[++i])
	{
		if (parse->task[i] && parse->task[i]->cmd)
		{
			ft_free_array((void **)parse->task[i]->cmd);
			parse->task[i]->cmd = NULL;
		}

void	ft_free_env(t_parse *parse)
{
	ft_free_array((void **)parse->env);
}

void	ft_free_parsing(t_parse *parse)
{
	if (parse->task)
	{
		ft_free_task(parse);
		parse->task = NULL;
	}

void	ft_free_all(t_parse *parse)
{
	if (parse->task)
	{
		ft_free_task(parse);
		parse->task = NULL;
	}

static void	ft_arrtolower(char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			arr[i][j] = ft_tolower(arr[i][j]);
			j++;
		}

static bool	ft_isfirst(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	**strs;
	bool	result;

	strs = ft_dupentries(s1, s2);
	if (!strs)
		return (true);
	i = 0;
	j = 0;
	while (strs[0][i] && !ft_isalpha(strs[0][i]))
		i++;
	while (strs[1][j] && !ft_isalpha(strs[1][j]))
		j++;
	ft_arrtolower(strs);
	while (strs[0] && strs[1] && strs[0][i] == strs[1][j] && i++ && j++)
		;
	result = strs[0][i] > strs[1][j];
	ft_free_array((void **)strs);
	return (result);
}

static void	ft_lstswap(t_list *lst)
{
	void	*tmp;

	tmp = NULL;
	tmp = lst->content;
	lst->content = lst->next->content;
	lst->next->content = tmp;
}

void	ft_sortwc(t_list **lst)
{
	char	*s1;
	char	*s2;
	t_list	*current;
	int		i;

	i = -1;
	while (++i < ft_lstsize(*lst))
	{
		current = *lst;
		while (current)
		{
			s1 = current->content;
			if (current->next)
				s2 = current->next->content;
			else
				s2 = NULL;
			if (s2 && ft_isfirst(s1, s2))
				ft_lstswap(current);
			current = current->next;
		}

bool	ft_check_end_of_file(char *tmp, char *line, char *limiter)
{
	size_t	i;
	char	*str;
	size_t	len;

	i = ft_strlen(line);
	len = ft_strlen(limiter);
	if (!ft_strncmp(limiter, tmp, len))
		return (true);
	while (i > 0 && line[i - 1] != '\n')
		i--;
	str = ft_strjoin(&line[i], tmp);
	if (!str)
		return (false);
	if (!ft_strncmp(limiter, str, len))
	{
		free(str);
		return (true);
	}

void	ft_error_heredoc(int n, char *limiter)
{
	if (n == 0)
	{
		ft_putstr_fd("\e[0;36mwarning: here-document\
 delimited by end-of-file (wanted `", 2);
		write(2, limiter, ft_strlen(limiter));
		ft_putendl_fd("')\e[0m", 2);
	}

int	ft_fail_open(char *name, char *line, char *tmp)
{
	free(name);
	free(line);
	free(tmp);
	return (-1);
}

int	pre_check(int check, char c)
{
	if (check == 0 && c == '$')
		return (1);
	return (0);
}

static bool	ft_match_start(t_wc *wc, char *str, char **file)
{
	size_t	len;

	if (wc->start && str[0] == *file[0])
	{
		len = ft_strlen(wc->start);
		if (!ft_strncmp(*file, wc->start, len))
		{
			*file += len;
			return (true);
		}

static bool	ft_match_middle(t_list **c, char **file, t_wc *wc, t_list **lst)
{
	size_t	len;
	t_list	*current;

	current = *c;
	if (current)
	{
		len = ft_strlen(current->content);
		if (!ft_strncmp(*file, current->content, len))
		{
			*file += len;
			*c = current->next;
			if (*c == NULL && !wc->end && !*file)
			{
				ft_putstr_fd("dans middle: ", 1);
				ft_putendl_fd(wc->str, 1);
				ft_lstadd_back(lst, ft_lstnew(ft_strdup(wc->str)));
				return (true);
			}

static bool	ft_match_end(t_list **lst, t_wc *wc, char *str, char **file)
{
	size_t	len;
	size_t	file_len;

	file_len = ft_strlen(*file);
	if (wc->end)
	{
		len = ft_strlen(wc->end);
		if (file_len == len && !ft_strncmp(*file, wc->end, len))
		{
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(str)));
			return (true);
		}

static void	ft_match_tempalte(t_wc *wc, t_list **lst, char *str)
{
	t_list	*current;
	char	*file;

	wc->str = str;
	current = wc->middle;
	file = str;
	if (((wc->start && ft_strncmp(wc->start, ".", 1)) || !wc->start)
		&& !ft_strncmp(str, ".", 1))
		return ;
	while (*file)
	{
		if (!ft_match_start(wc, str, &file))
			return ;
		if (ft_match_middle(&current, &file, wc, lst))
			continue ;
		if (ft_match_end(lst, wc, str, &file))
			return ;
	}

static void	ft_add_value(t_parse *parse, char **var, char **str, int check)
{
	if (check == 1)
		*str = ft_strfjoin(*str, "$", 1);
	else if (*var && (*var)[0] != '\0' && ft_getenv(parse, *var))
		*str = ft_strfjoin(*str, ft_getenv(parse, *var), 1);
	free(*var);
	*var = NULL;
	if (!*str)
		return ;
}

static void	ft_write_file(t_parse *parse, char *line, int index, char *tmp)
{
	char	*str;
	char	*var;

	free(tmp);
	str = (char *)ft_calloc(1, sizeof(char));
	if (!str)
		return ;
	var = NULL;
	if (!parse->redirect[index]->in_quote)
	{
		str = ft_replace_var(parse, line, str, var);
		ft_putstr_fd(str, parse->redirect[index]->fd);
		free(str);
	}

static void	ft_read_line(t_parse *parse, char *line, char *tmp, int index)
{
	while (true)
	{
		free(tmp);
		tmp = readline("heredoc>");
		if (tmp)
		{
			tmp = ft_strfjoin(tmp, "\n", 1);
			if (!tmp)
				break ;
			if (!ft_check_end_of_file(tmp, line, parse->redirect[index]->file))
			{
				line = ft_strfjoin(line, tmp, 1);
				if (!line)
					break ;
			}

int	ft_here_doc(t_parse *parse, int index)
{
	char	*tmp;
	char	*line;
	char	*name;

	name = NULL;
	line = (char *)ft_calloc(1, sizeof(char));
	if (!line)
		return (-1);
	tmp = (char *)ft_calloc(1, sizeof(char));
	if (!tmp)
		free(line);
	if (!tmp)
		return (-1);
	parse->redirect[index]->fd = ft_open_tmp(&name);
	if (parse->redirect[index]->fd < 0)
		return (ft_fail_open(name, line, tmp));
	ft_read_line(parse, line, tmp, index);
	free(parse->redirect[index]->file);
	parse->redirect[index]->file = name;
	close(parse->redirect[index]->fd);
	parse->redirect[index]->fd = open(parse->redirect[index]->file, O_RDONLY);
	return (parse->redirect[index]->fd);
}

void	ft_free_wc(t_wc *wc)
{
	if (!wc)
		return ;
	if (wc->start)
	{
		free(wc->start);
		wc->start = NULL;
	}

void	ft_unquote(t_wc *wc)
{
	t_list	*current;

	current = wc->middle;
	if (wc->start && ft_quoted(wc->start))
		wc->start = ft_strqcpy(wc->start);
	if (wc->end && ft_quoted(wc->end))
		wc->end = ft_strqcpy(wc->end);
	while (current)
	{
		if (ft_quoted(current->content))
			current->content = ft_strqcpy(current->content);
		current = current->next;
	}

void	ft_lstinsert(t_list **lst, t_list *addlst, t_list **ptr)
{
	t_list	*current;
	t_list	*last;
	t_list	*tmp;

	current = (t_list *)*lst;
	last = ft_lstlast(addlst);
	tmp = *ptr;
	if (*lst == *ptr)
	{
		free(tmp->content);
		free(*lst);
		*lst = addlst;
		*ptr = last;
		return ;
	}

static void	ft_arrcpy(char ***arr, char **new_arr, size_t *i)
{
	while ((*arr)[*i])
	{
		new_arr[*i] = ft_strdup((*arr)[*i]);
		if (!new_arr[*i])
		{
			ft_free_array(*(void **)new_arr);
			return ;
		}

static void	ft_tokcpy(char ***arr, char *str, size_t n)
{
	char	**new_arr;
	size_t	arr_len;
	size_t	i;

	i = 0;
	arr_len = ft_arrlen(*(void **)arr);
	new_arr = (char **)ft_calloc(arr_len + 2, sizeof(char *));
	if (!new_arr)
		return ;
	ft_arrcpy(arr, new_arr, &i);
	new_arr[i] = (char *)ft_calloc(n + 1, sizeof(char));
	if (!new_arr[i])
	{
		ft_free_array((void **)new_arr);
		return ;
	}

static void	init_tok(t_tok *tok)
{
	tok->i = -1;
	tok->j = -1;
	tok->last = 0;
	tok->in_quotes = -1;
}

int	ft_open_tmp(char **name)
{
	int		fd;

	*name = ft_rand_str(52);
	if (!*name)
		return (-1);
	if (!access(*name, F_OK))
	{
		free(*name);
		ft_open_tmp(name);
	}

size_t	ft_arrlen(void **env)
{
	size_t	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

void	ft_lstto_arr(t_object *task, t_list *lst)
{
	size_t	j;
	size_t	lst_len;
	t_list	*tmp;
	char	**n_arr;

	j = 0;
	lst_len = ft_lstsize(lst);
	n_arr = (char **)ft_calloc(lst_len + 1, sizeof(char *));
	if (!n_arr)
	{
		ft_lstclear(&lst, free);
		return ;
	}

