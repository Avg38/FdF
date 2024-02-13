NAME	= fdf
SRCS	= 	srcs/fdf.c\
			srcs/draw.c\
			srcs/hooks.c\
			srcs/limits.c\
			srcs/points.c\
			srcs/start.c

OBJS	= $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -rf

all:	force $(NAME)

$(NAME):	$(OBJS)
		gcc $(CFLAGS) -Iinclude -Ilibft $(OBJS) -o $(NAME) -Llibft -lft

%.o:	%.c include/fdf.h 
	gcc $(CFLAGS) -c $< -o $@ -Iinclude -Ilibft

force:
	make -C libft

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re force