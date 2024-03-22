/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:18:18 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/22 16:52:03 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define DATA matrix[0][0]

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
	int		is_isometric;
	int		height;
	int		width;
	double	scale;
	double	angle;
	double	depth;
	int		offset_x;
	int		offset_y;
	void	*mlx;
	void	*win;
	t_img	*img;
}	t_matrix;

enum
{
	UP = 65362,
	DOWN = 65364,
	LEFT = 65361,
	RIGHT = 65363,
	SPACE = 32,
	MINUS = 65453,
	PLUS = 65451,
	STAR = 65450,
	DIV = 65455,
	ESC = 65307,
	UP_Z = 65365,
	DOWN_Z = 65366,
	SIX = 65432
};

char		**ft_split_color(char *s);
void		display_tab2d(char **s, int height);
void		free_2d(char **str, int len);
void		free_matrix(t_matrix **matrix, int height);
void		display_matrix(t_matrix **matrix);
void		get_height(char *av, int *height);
void		get_width(char *line, int *width);
char		**line_parser(char *line);
void		fill_zero(t_matrix *matrix, int width);
void		fill_matrix(char *file, t_matrix **matrix);
void		fill_data(char **line, t_matrix **matrix, int y);
void		size_matrix(char *file, int *height, int *width);
t_matrix	**alloc_matrix(int height, int width);
void		ft_exit(char *msg, t_matrix **matrix, int height);
// void	height_width(char *file);
void		set_DATA(t_matrix **matrix, int height, int width);
void		check_args(int ac, char *file);

#endif
