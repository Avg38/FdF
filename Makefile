# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 15:25:21 by avialle-          #+#    #+#              #
#    Updated: 2024/02/23 18:37:40 by avialle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL: all

NAME	=	fdf

SRCS	=	srcs/main.c\
			srcs/list.c\
			srcs/errors.c\
			srcs/display.c\
			srcs/free.c\
			srcs/map_parser.c\
			srcs/ft_split_color.c

OBJS	= $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -rf

all:	force $(NAME)

$(NAME):	$(OBJS) libft/libft.a
		gcc $(CFLAGS) -Iinclude -Ilibft $(OBJS) -o $(NAME) -Llibft -lft

%.o:	%.c include/fdf.h libft/libft.h Makefile libft/libft.a
	gcc $(CFLAGS) -c $< -o $@

force:
	make -C libft

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re force