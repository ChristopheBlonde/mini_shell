# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cblonde <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 12:48:51 by cblonde           #+#    #+#              #
#    Updated: 2024/04/04 12:42:28 by cblonde          ###   ########.fr        #
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
	  $(UTILS)ft_here_doc.c $(TERM)ft_init_term.c

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
