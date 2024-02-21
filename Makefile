# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 15:25:21 by avialle-          #+#    #+#              #
#    Updated: 2024/02/21 15:32:54 by avialle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL: all

NAME	=	fdf

SRCS	=	srcs/main.c\
			srcs/list.c\
			srcs/errors.c\
			srcs/ft_split_color.c

OBJS	= $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -rf

all:	$(NAME)

$(NAME):	$(OBJS)
		gcc $(CFLAGS) -Iinclude -Ilibft $(OBJS) -o $(NAME) -Llibft -lft

%.o:	%.c include/fdf.h
	gcc $(CFLAGS) -c $< -o $@

force:
	make -C libft

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re force