# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 12:48:51 by cblonde           #+#    #+#              #
#    Updated: 2024/04/29 14:58:56 by cblonde          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wextra -Wall -gdwarf-4

INCLUDE = -Iinclude -Ilib

LIBRARIES = -Llib -lft -lreadline

LIBFT = lib/libft.a

NAME = minishell

UTILS = src/utils/

PARSE = src/parsing/

SYNTAX = src/parsing/syntax/

BUILTIN = src/builtin/

SRC = src/main.c $(PARSE)ft_parse_env.c $(UTILS)ft_free_array.c $(UTILS)ft_arrlen.c\
	  $(BUILTIN)ft_export.c $(BUILTIN)ft_unset.c $(BUILTIN)ft_get_index_env.c\
	  $(BUILTIN)ft_getenv.c $(BUILTIN)ft_env.c $(PARSE)ft_parse_token.c\
	  $(UTILS)ft_strtok.c $(UTILS)ft_get_random.c $(UTILS)ft_tmp_file.c\
	  $(UTILS)ft_here_doc.c $(UTILS)ft_utils_heredoc.c \
	  $(PARSE)ft_objectify.c $(PARSE)ft_quote_handler.c $(PARSE)ft_redirect.c\
	  $(PARSE)ft_utils_quote.c $(UTILS)ft_free_all.c $(UTILS)ft_free_utils.c\
	  $(PARSE)ft_utils_redirect.c $(PARSE)ft_clean_cmd.c $(UTILS)ft_listdir.c\
	  $(PARSE)ft_build_wildcard.c $(UTILS)ft_utils_wildcard.c\
	  $(UTILS)ft_utils_list.c $(UTILS)ft_sortwildcard.c\
	  $(PARSE)ft_utils_quote.c $(UTILS)ft_free_all.c $(SYNTAX)ft_and_operator_handler.c\
	  $(SYNTAX)ft_syntax_errors_handler.c $(SYNTAX)ft_parenthesis_handler.c

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
