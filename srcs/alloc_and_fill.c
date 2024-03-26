/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:56:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/26 14:41:33 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_imgs	init_new_img(t_matrix	**matrix)
{
	t_imgs	img;

	ft_bzero(&img, sizeof(t_imgs));
	img.img = mlx_new_image(DATA.mlx, WIDTH, HEIGHT);
	if (!img.img)
		ft_exit("Error, init_new_image", matrix, DATA.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_len, &img.endian);
	if (!img.addr)
		ft_exit("Error, init_new_image", matrix, DATA.height);
	return (img);
}

void	set_data(t_matrix **matrix, int height, int width)
{
	DATA.height = height;
	DATA.width = width;
	DATA.mlx = mlx_init();
	if (!DATA.mlx)
		ft_exit("Error DATA.mlx\n", matrix, DATA.height);
	DATA.win = mlx_new_window(DATA.mlx, WIDTH, HEIGHT, "FDF");
	if (!DATA.win)
		ft_exit("Error DATA.win\n", matrix, DATA.height);
	DATA.imgs = init_new_img(matrix);
	if (mlx_put_image_to_window(DATA.mlx, DATA.win, DATA.imgs.img, 0, 0) < 0)
		ft_exit("Error mlx_put_img_to_win\n", matrix, DATA.height);
}

void	fill_data(char **line, t_matrix **matrix, int y)
{
	char	**split;
	int		x;

	x = 0;
	while (x < DATA.width)
	{
		matrix[y][x].y = y;
		matrix[y][x].x = x;
		split = ft_split_color(line[x]);
		if (!split || !split[0])
			return (free_2d(line, x));
		matrix[y][x].z = ft_atoi(split[0]);
		matrix[y][x].color = ft_atoi_base(split[1], "0123456789abcdef");
		matrix[y][x].is_valid = 1;
		free_2d(split, 2);
		x++;
	}
	free_2d(line, x);
}

void	fill_matrix(char *file, t_matrix **matrix)
{
	int	fd;
	int	y;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error! Bad fd or file empty", matrix, DATA.height);
	y = -1;
	while (++y < DATA.height)
		fill_data(line_parser(get_next_line(fd)), matrix, y);
	close(fd);
}

void	fill_zero(t_matrix *matrix)
{
	matrix->x = 0;
	matrix->y = 0;
	matrix->z = 0;
	matrix->color = 0;
	matrix->x_proj = 0;
	matrix->y_proj = 0;
	matrix->z_proj = 0;
	matrix->is_valid = 0;
	matrix->is_isometric = 0;
	matrix->height = 0;
	matrix->width = 0;
	matrix->scale = 0;
	matrix->angle = 0;
	matrix->depth = 0;
	matrix->offset_x = 0;
	matrix->offset_y = 0;
	matrix->rot_x = 0;
	matrix->rot_y = 0;
	matrix->rot_z = 0;
	matrix->mlx = NULL;
	matrix->win = NULL;
}

t_matrix	**alloc_matrix(int height, int width)
{
	t_matrix	**matrix;
	int			y;
	int			x;

	matrix = (t_matrix **)malloc(height * sizeof(t_matrix *));
	if (!matrix)
		return (ft_exit("malloc matrix failed", NULL, 0), NULL);
	y = -1;
	while (++y < height)
	{
		matrix[y] = (t_matrix *)malloc((width + 1) * sizeof(t_matrix));
		if (!matrix[y])
			return (ft_exit("malloc matrix element failed", matrix, y), NULL);
	}
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x <= width)
			fill_zero(&matrix[y][x]);
	}
	return (matrix);
}
