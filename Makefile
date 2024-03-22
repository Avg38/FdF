.DEFAULT_GOAL: all

NAME	=	fdf

SRCS	=	srcs/main.c\
			srcs/errors.c\
			srcs/display.c\
			srcs/utils.c\
			srcs/ft_split_color.c\
			srcs/alloc_and_fill.c\
			srcs/size_matrix.c

OBJS	= $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -Llibft -lft -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
RM	= rm -rf

all:	force $(NAME)
		@echo "Makefile compiled."

$(NAME):	$(OBJS) libft/libft.a 
		gcc $(CFLAGS) -Iinclude -Ilibft $(OBJS) -o $(NAME) $(LDFLAGS)

%.o:	%.c include/fdf.h libft/libft.h Makefile libft/libft.a
	gcc $(CFLAGS) -c $< -o $@

force:
	@make -C libft/ -s
	@make -C minilibx-linux/

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re force