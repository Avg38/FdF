/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:18:18 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/22 15:16:22 by avialle-         ###   ########.fr       */
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

char	**ft_split_color(char *s);
void	display_tab2d(char **s, int height);
void	free_2d(char **str, int len);
void	free_matrix(t_matrix **matrix, int height);
void	display_matrix(t_matrix **matrix);
void	get_height(char *av, int *height);
void	get_width(char *line, int *width);
char	**line_parser(char *line);
void	fill_data(char **line, t_matrix **matrix, int y);
void	set_size_matrix(char *file,  int *height, int *width);
t_matrix	**alloc_matrix(int height, int width);
t_matrix	*ft_calloc_fdf(t_matrix *matrix, int width);
void	ft_exit(char *msg, t_matrix **matrix, int height);
// void	height_width(char *file);
void	set_DATA(t_matrix **matrix, int height, int width);
void	check_args(int ac, char *file);

#endif
