# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 15:03:27 by oamairi           #+#    #+#              #
#    Updated: 2025/07/16 15:35:59 by oamairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		pipex.c

OBJS =		$(SRCS:.c=.o)

NAME =		pipex

CC =		gcc

RM =		rm -f

CFLAGS =	-Wall -Wextra -Werror libft/libft.a ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all