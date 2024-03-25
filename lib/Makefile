# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 12:51:32 by cblonde           #+#    #+#              #
#    Updated: 2024/03/25 13:45:04 by tsadouk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
DEPENDENCES = ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			  ft_toupper.c ft_tolower.c ft_bzero.c ft_memset.c ft_memcpy.c ft_memmove.c\
			  ft_strlcpy.c ft_strlcat.c ft_memcmp.c ft_memchr.c ft_strchr.c ft_strrchr.c\
			  ft_strncmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_putchar_fd.c\
			  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_substr.c ft_strjoin.c\
			  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_printf.c\
			  ft_putlchar.c ft_putlnbr_base.c ft_putlstr.c ft_putlhex.c ft_get_next_line.c\
			  ft_strfjoin.c ft_isspace.c
DEPENDENCES_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
					ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJDIR = obj
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(DEPENDENCES))
OBJ_BONUS = $(patsubst %.c,$(OBJDIR)/%.o,$(DEPENDENCES_BONUS))
NAME = libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus : $(OBJ) $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJDIR)

fclean : clean 
	rm -rf $(NAME) libft.so a.out test

re : fclean $(NAME)

.PHONY: bonus all clean fclean re
