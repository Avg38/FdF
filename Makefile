.DEFAULT_GOAL: all

NAME	=	fdf
NAME_BONUS	=	fdf_bonus

SRCS	=	src/main.c\
			src/frame/create_frame.c\
			src/frame/draw_line.c\
			src/frame/apply_rotation.c\
			src/frame/apply_params.c\
			src/init/size_matrix.c\
			src/init/init_matrix.c\
			src/init/fill_matrix.c\
			src/init/errors.c\
			src/utils/utils.c

SRCS_BONUS	=	src_bonus/main.c\
			src_bonus/frame/color.c\
			src_bonus/frame/create_frame.c\
			src_bonus/frame/draw_line.c\
			src_bonus/frame/apply_rotation.c\
			src_bonus/frame/apply_params.c\
			src_bonus/init/size_matrix.c\
			src_bonus/init/init_matrix.c\
			src_bonus/init/fill_matrix.c\
			src_bonus/init/errors.c\
			src_bonus/key_manager/manage_key.c\
			src_bonus/key_manager/do_key1.c\
			src_bonus/key_manager/do_key2.c\
			src_bonus/utils/utils.c

OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus
# OBJS	= $(SRCS:.c=.o)
OBJS	= $(patsubst src/%.c, obj/%.o, $(SRCS))
OBJS_BONUS	= $(patsubst src_bonus/%.c, obj_bonus/%.o, $(SRCS_BONUS))
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -Llibft -lft -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
RM	= rm -rf

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)/frame
		@mkdir -p $(OBJ_DIR)/init
		@mkdir -p $(OBJ_DIR)/key_manager
		@mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR_BONUS):
		@mkdir -p $(OBJ_DIR_BONUS)
		@mkdir -p $(OBJ_DIR_BONUS)/frame
		@mkdir -p $(OBJ_DIR_BONUS)/init
		@mkdir -p $(OBJ_DIR_BONUS)/key_manager
		@mkdir -p $(OBJ_DIR_BONUS)/utils

all:	force $(NAME)
		@echo "FdF compiled."

bonus:	force $(NAME_BONUS)
		@echo "FdF Bonus compiled."

$(NAME):	$(OBJS) libft/libft.a include/fdf.h
		@gcc $(CFLAGS) -Iinclude -Ilibft $(OBJS) -o $(NAME) $(LDFLAGS)

$(NAME_BONUS):	$(OBJS_BONUS) libft/libft.a include/fdf_bonus.h
		@gcc $(CFLAGS) -Iinclude -Ilibft $(OBJS_BONUS) -o $(NAME_BONUS) $(LDFLAGS)

obj/%.o:	src/%.c include/fdf.h libft/libft.h Makefile libft/libft.a | $(OBJ_DIR)
		@gcc $(CFLAGS) -c $< -o $@

obj_bonus/%.o:	src_bonus/%.c include/fdf_bonus.h libft/libft.h Makefile libft/libft.a | $(OBJ_DIR_BONUS)
		@gcc $(CFLAGS) -c $< -o $@

force:
		@make -C libft/ -s
		@make -C minilibx-linux/ -s

clean:
		@$(RM) -r $(OBJ_DIR)
		@$(RM) -r $(OBJ_DIR_BONUS)

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(NAME_BONUS)

re:		fclean all

reb:		fclean bonus

.PHONY: all clean fclean re force