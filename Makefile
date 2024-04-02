.DEFAULT_GOAL: all

NAME		=	fdf
NAME_BONUS	=	fdf_bonus

SRCS		=	src/main.c\
				src/frame/apply_params.c\
				src/frame/apply_rotation.c\
				src/frame/create_frame.c\
				src/frame/draw_line.c\
				src/init/close_program.c\
				src/init/fill_matrix.c\
				src/init/init_matrix.c\
				src/init/size_matrix.c

SRCS_BONUS	=	src_bonus/main.c\
				src_bonus/frame/apply_params.c\
				src_bonus/frame/apply_rotation.c\
				src_bonus/frame/color.c\
				src_bonus/frame/create_frame.c\
				src_bonus/frame/draw_line.c\
				src_bonus/init/close_program.c\
				src_bonus/init/fill_matrix.c\
				src_bonus/init/init_matrix.c\
				src_bonus/init/size_matrix.c\
				src_bonus/key_manager/do_key1.c\
				src_bonus/key_manager/do_key2.c\
				src_bonus/key_manager/manage_key.c

OBJ_DIR			=	obj
OBJ_DIR_BONUS	=	obj_bonus
OBJS			=	$(patsubst src/%.c, obj/%.o, $(SRCS))
OBJS_BONUS		=	$(patsubst src_bonus/%.c, obj_bonus/%.o, $(SRCS_BONUS))
CFLAGS			=	-Wall -Wextra -Werror
LDFLAGS			=	-Llibft -lft -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
RM				=	rm -rf
COLOR_RESET		=	\033[0m
COLOR_GREEN		=	\033[0;32m

all:	force $(NAME)
		@echo "$(COLOR_GREEN)FdF compiled.$(COLOR_RESET)"

bonus:	force $(NAME_BONUS)
		@echo "$(COLOR_GREEN)FdF Bonus compiled.$(COLOR_RESET)"

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)/frame
		@mkdir -p $(OBJ_DIR)/init

$(OBJ_DIR_BONUS):
		@mkdir -p $(OBJ_DIR_BONUS)
		@mkdir -p $(OBJ_DIR_BONUS)/frame
		@mkdir -p $(OBJ_DIR_BONUS)/init
		@mkdir -p $(OBJ_DIR_BONUS)/key_manager
		@mkdir -p $(OBJ_DIR_BONUS)/utils

$(NAME):	$(OBJS) libft/libft.a include/fdf.h
		@gcc $(CFLAGS) -Iinclude -Ilibft $(OBJS) -o $(NAME) $(LDFLAGS)

$(NAME_BONUS):	$(OBJS_BONUS) libft/libft.a include/fdf_bonus.h
		@gcc $(CFLAGS) -Iinclude -Ilibft $(OBJS_BONUS) -o $(NAME_BONUS) $(LDFLAGS)

obj/%.o:	src/%.c include/fdf.h libft/libft.h Makefile libft/libft.a | $(OBJ_DIR)
		@gcc $(CFLAGS) -Iinclude -Ilibft -c $< -o $@

obj_bonus/%.o:	src_bonus/%.c include/fdf_bonus.h libft/libft.h Makefile libft/libft.a | $(OBJ_DIR_BONUS)
		@gcc $(CFLAGS) -c $< -o $@

force:
		@make -C libft/ -s
		@make -C minilibx-linux/ -s

clean:
		@$(RM) -r $(OBJ_DIR)
		@$(RM) -r $(OBJ_DIR_BONUS)
		@make clean -C libft -s
		@make clean -C minilibx-linux -s
		@echo "$(COLOR_GREEN)FdF cleaned.$(COLOR_RESET)"

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(NAME_BONUS)
		@make fclean -C libft -s
		@make clean -C minilibx-linux -s

re:		fclean all

reb:	fclean bonus

.PHONY: all clean fclean re force bonus reb