/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:18:18 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 16:16:48 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define DATA matrix[0][0]
# define HEIGHT 1080
# define WIDTH 1920
# define SCALE_FACTOR 0.5

typedef struct s_imgs
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		x_diff;
	int		y_diff;
	int		x_step;
	int		y_step;
	int		decision;
	int		gradient;
	int		diagonal;
}	t_imgs;

typedef struct s_argb
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_argb;

typedef struct s_matrix
{
	int		x;
	int		y;
	int		z;
	int		color;
	int		x_proj;
	int		y_proj;
	int		z_proj;
	int		is_valid;
	int		isometric;
	int		height;
	int		width;
	double	scale;
	double	depth;
	int		offset_x;
	int		offset_y;
	double	rot_x;
	double	rot_y;
	double	rot_z;
	void	*mlx;
	void	*win;
	t_imgs	imgs;
}	t_matrix;

enum
{
	W = 119,
	S = 115,
	A = 97,
	D = 100,
	UP = 65362,
	DOWN = 65364,
	LEFT = 65361,
	RIGHT = 65363,
	MINUS = 65453,
	PLUS = 65451,
	STAR = 65450,
	DIV = 65455,
	ESC = 65307,
	SPACE = 32,
	UP_Z = 65365,
	DOWN_Z = 65366,
	G = 103,
	C = 99,
	V = 118
};

// ******************MAIN
void		check_args(int ac, char *file);
t_matrix	**init_fdf(char *file, t_matrix **matrix);

// ******************INIT
// ft_split_color.c
char		**ft_split_color(char *s);
char		**extract_first_part(char *s, int *i);
// errors.c
void		free_2d(char **str, int len);
void		free_matrix(t_matrix **matrix, int height);
void		ft_exit(char *msg, t_matrix **matrix, int height);
void		height_width(char *file);
// size_matrix.c
void		size_matrix(char *file, int *height, int *width);
void		get_height(char *av, int *height);
void		get_width(char *line, int *width);
// init_matrix.c
t_matrix	**alloc_matrix(int height, int width);
void		fill_zero(t_matrix *matrix);
void		init_proj(t_matrix **matrix);
void		init_data(t_matrix **matrix, int height, int width);
t_imgs		init_new_img(t_matrix	**matrix);
// fill_matrix.c
void		fill_matrix(char *file, t_matrix **matrix);
void		fill_zero(t_matrix *matrix);
void		fill_data(char **line, t_matrix **matrix, int y);
void		fill_color(t_matrix **matrix);

// ******************FRAME
// create_frame.c
int			frame(t_matrix **matrix);
void		transform_img(t_matrix **matrix);
void		init_proj_map(t_matrix **matrix);
// apply_params.c
void		apply_scaling(t_matrix *point, t_matrix **matrix);
void		apply_isometric(t_matrix *point);
void		apply_offset(t_matrix *point, t_matrix **matrix);
void		mod_2d(t_matrix **matrix);
// apply_rotation.c
void		apply_rotation(t_matrix *point, t_matrix **matrix);
void		apply_rot_x(t_matrix *point, double cos_a, double sin_a);
void		apply_rot_y(t_matrix *point, double cos_a, double sin_a);
void		apply_rot_z(t_matrix *point, double cos_a, double sin_a);
// draw_line.c
void		draw_line(t_imgs imgs, t_matrix p0, t_matrix p1);
void		put_pixel(t_imgs imgs, int x, int y, int color);
void		draw_acute_slope(t_imgs imgs, t_matrix p0, t_matrix p1);
void		draw_obtus_slope(t_imgs imgs, t_matrix p0, t_matrix p1);
void		init_step(t_imgs *imgs, t_matrix p0, t_matrix p1);

// ******************KEY_MANAGER
// manage_key.c
int			close_win(t_matrix **matrix);
int			is_key(int key);
void		do_key(int key, t_matrix **matrix);
int			key_handler(int key, t_matrix **matrix);
// do_key1.c
void		do_key(int key, t_matrix **matrix);
void		center_key(t_matrix **matrix);
void		isometric_key(t_matrix **matrix);
void		diagonal_key(t_matrix **matrix);
// do_key2.c
void		gradient_key(t_matrix **matrix);
void		rot_key(int key, t_matrix **matrix);
void		offset_key(int key, t_matrix **matrix);
void		scale_key(int key, t_matrix **matrix);
void		depth_key(int key, t_matrix **matrix);
// color.c
int			strhexa_to_colorint(char *strhexa);
t_argb		create_argb(int color);
int			create_color_gradient(float delta, t_argb color1, t_argb color2);
int			process_color(int curr_steps, int tot_steps,
				int color_ini, int color_end);

// ******************UTILS
// utils.c
void		display_tab2d(char **s, int height);
void		display_matrix(t_matrix **matrix);
char		**line_parser(char *line);
#endif
