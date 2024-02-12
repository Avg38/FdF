SRCS	= srcs/main.c
OBJS	= $(SRCS:.c=.o)
NAME	= libft.a
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -rf

all:	$(NAME)

$(NAME):	$(OBJS)
		@ar rc $(NAME) $(OBJS)

%.o:	%.c include/fdf.h 
	@gcc $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re