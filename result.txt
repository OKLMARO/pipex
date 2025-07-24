# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 15:03:27 by oamairi           #+#    #+#              #
#    Updated: 2025/07/24 14:50:19 by oamairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		pipex.c pipex_utils.c

OBJS =		$(SRCS:.c=.o)

NAME =		pipex

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = libft/libft.a
PRINTF = ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft bonus
	$(MAKE) -C ft_printf
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C ft_printf fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re