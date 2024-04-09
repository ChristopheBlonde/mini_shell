# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 12:48:51 by cblonde           #+#    #+#              #
#    Updated: 2024/04/09 15:43:35 by cblonde          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

INCLUDE = -Iinclude -Ilib

LIBRARIES = -Llib -lft -lncurses -lreadline

LIBFT = lib/libft.a

NAME = minishell

UTILS = src/utils/

PARSE = src/parsing/

BUILTIN = src/builtin/

TERM = src/term/

SRC = src/main.c $(PARSE)ft_parse_env.c $(UTILS)ft_free_array.c $(UTILS)ft_arrlen.c\
	  $(BUILTIN)ft_export.c $(BUILTIN)ft_unset.c $(BUILTIN)ft_get_index_env.c\
	  $(BUILTIN)ft_getenv.c $(BUILTIN)ft_env.c $(PARSE)ft_parse_token.c\
	  $(UTILS)ft_strtok.c $(UTILS)ft_get_random.c $(UTILS)ft_tmp_file.c\
	  $(UTILS)ft_here_doc.c $(UTILS)ft_utils_heredoc.c $(TERM)ft_init_term.c\
	  $(PARSE)ft_objectify.c $(PARSE)ft_quote_handeler.c $(PARSE)ft_redirect.c\
	  $(PARSE)ft_utils_quote.c $(UTILS)ft_free_all.c

all : $(NAME)

$(LIBFT) :
	make -C lib --no-print-directory

OBJ = $(SRC:.c=.o)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME) $(LIBRARIES)

clean :
	rm -rf $(OBJ)
	make clean -C lib --no-print-directory

fclean : clean
	rm -rf $(NAME)
	make fclean -C lib --no-print-directory

re : fclean $(NAME)

.PHONY : all clean fclean re
