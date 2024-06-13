# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 12:48:51 by cblonde           #+#    #+#              #
#    Updated: 2024/06/13 08:58:45 by cblonde          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Werror -Wextra -Wall -gdwarf-4

INCLUDE = -Iinclude -Ilib -I/opt/homebrew/opt/readline/include

LIBRARIES = -Llib -lft -lreadline -L/opt/homebrew/opt/readline/lib

LIBFT = lib/libft.a

NAME = minishell

UTILS = src/utils/

PARSE = src/parsing/

SYNTAX = src/parsing/syntax/

BUILTIN = src/builtin/

EXEC = src/execution/

SIGNAL = src/signal/

SRC = src/main.c $(PARSE)ft_parse_env.c $(UTILS)ft_free_array.c\
	  $(UTILS)ft_arrlen.c\
	  $(BUILTIN)ft_export.c $(BUILTIN)ft_unset.c $(BUILTIN)ft_get_index_env.c\
	  $(BUILTIN)ft_getenv.c  $(BUILTIN)ft_echo.c $(BUILTIN)ft_env.c\
	  $(PARSE)ft_parse_token.c $(EXEC)ft_execution.c $(EXEC)ft_exec_redirect.c\
	  $(UTILS)ft_strtok.c $(UTILS)ft_get_random.c $(UTILS)ft_tmp_file.c\
	  $(UTILS)ft_here_doc.c $(UTILS)ft_utils_heredoc.c \
	  $(PARSE)ft_objectify.c $(PARSE)ft_quote_handler.c $(PARSE)ft_redirect.c\
	  $(PARSE)ft_utils_quote.c $(UTILS)ft_free_all.c $(UTILS)ft_free_utils.c\
	  $(PARSE)ft_utils_redirect.c $(PARSE)ft_clean_cmd.c $(UTILS)ft_listdir.c\
	  $(PARSE)ft_build_wildcard.c $(UTILS)ft_utils_wildcard.c\
	  $(UTILS)ft_utils_list.c $(UTILS)ft_sortwildcard.c\
	  $(SYNTAX)ft_and_operator_handler.c $(SYNTAX)ft_or_operator_handler.c\
	  $(SYNTAX)ft_parenthesis_handler.c $(SYNTAX)ft_prompt_errors.c\
	  $(SYNTAX)ft_syntax_errors_handler.c $(UTILS)ft_sortarray.c\
	  $(BUILTIN)ft_checkbuiltin.c $(PARSE)ft_init_data.c\
	  $(BUILTIN)ft_utils_export.c $(BUILTIN)ft_pwd.c $(BUILTIN)ft_cd.c\
	  $(SYNTAX)ft_temp.c $(SYNTAX)ft_env_handler.c $(BUILTIN)ft_utils_env_export.c\
	  $(EXEC)ft_get_path.c $(SYNTAX)ft_utils_env_handler.c $(EXEC)ft_utils_exec.c $(SIGNAL)ft_signal.c \
	  $(BUILTIN)ft_exit.c $(SYNTAX)ft_env_utils2.c $(EXEC)ft_utils_exec_builtin.c $(EXEC)ft_fd_utils.c $(PARSE)ft_utils_clean.c
	  
OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all : $(NAME)

$(LIBFT) :
	make bonus -C lib --no-print-directory

$(OBJ_DIR)%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME) $(LIBRARIES)

clean :
	rm -rf $(OBJ_DIR)
	make clean -C lib --no-print-directory

fclean : clean
	rm -rf $(NAME)
	make fclean -C lib --no-print-directory

re : fclean $(NAME)

.PHONY : all clean fclean re
