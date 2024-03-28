/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:53:07 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 16:05:01 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define WIN_H 1080
# define WIN_W 1920
# define SCALE_FACTOR 0.8

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
}	t_imgs;

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

// ******************MAIN
void		check_args(int ac, char *file);

// ******************INIT
// close.c
void		free_2d(char **str, int len);
void		free_matrix(t_matrix **matrix, int height);
void		ft_exit(char *msg, t_matrix **matrix, int height);
int			close_win(t_matrix **matrix);
int			esc_handler(int key, t_matrix **matrix);
// size_matrix.c
void		size_matrix(char *file, int *height, int *width);
void		get_size(char *av, int *height, int *width);
int			get_width(char *line);
char		**line_parser(char *line);
// init_matrix.c
t_matrix	**init_fdf(char *file, t_matrix **matrix);
t_matrix	**alloc_matrix(int height, int width);
void		init_proj(t_matrix **matrix);
void		init_data(t_matrix **matrix, int height, int width);
t_imgs		init_new_img(t_matrix	**matrix);
// fill_matrix.c
void		fill_matrix(char *file, t_matrix **matrix);
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

#endif
