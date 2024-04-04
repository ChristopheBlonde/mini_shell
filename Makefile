# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 12:48:51 by cblonde           #+#    #+#              #
#    Updated: 2024/04/04 15:36:30 by tsadouk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

INCLUDE = -Iinclude -Ilib

LIBRARIES = -Llib -lft

LIBFT = lib/libft.a

NAME = minishell

UTILS = src/utils/

PARSE = src/parsing/

BUILTIN = src/builtin/

SRC = src/main.c $(PARSE)ft_parse_env.c $(UTILS)ft_free_array.c $(UTILS)ft_arrlen.c\
	  $(BUILTIN)ft_export.c $(BUILTIN)ft_unset.c $(BUILTIN)ft_get_index_env.c\
	  $(BUILTIN)ft_getenv.c $(BUILTIN)ft_env.c $(PARSE)ft_parse_token.c\
	  $(UTILS)ft_strtok.c	$(PARSE)ft_objectify.c $(PARSE)ft_quote_handeler.c

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
