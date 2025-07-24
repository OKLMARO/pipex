# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 22:34:10 by oamairi           #+#    #+#              #
#    Updated: 2025/07/24 14:55:35 by oamairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		ft_printf.c ft_putnbr.c \
			ft_strlen.c ft_putstr.c ft_putchar.c \
			ft_strdup.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_bonus)

fclean: clean
	$(RM) $(NAME)

re: fclean all