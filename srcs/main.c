/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/21 16:57:48 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	len_y(char *av)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd))
		i++;
	close(fd);
	return (i);
}

int	len_x(char *av)
{
	int				fd;
	int				i;
	unsigned int	wc;
	char			*line;
	int				is_separator;

	i = 0;
	is_separator = 1;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	wc = 0;
	while (line[i] || line[i] != '\n')
	{
		if (line[i] != ' ' && is_separator)
			wc++;
		is_separator = (' ' == line[i]);
		i++;
	}
	close(fd);
	return (i);
}

void	free2d(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_parser(char *str, int fd)
{
	close(fd);
	free(str);
}

void	display_map(t_map **map, int len_height, int len_width)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < len_height)
	{
		x = 0;
		while (x < len_width)
		{
			ft_printf("%d", map[y][x].z);
			x++;
		}
		y++;
	}
}



t_map	**set_t_point(char **non_parsed_map, int len_y, int len_x)
{
	t_map	**final_map;
	char	**split;
	int		y;
	int		x;

	y = 0;
	x = 0;
	final_map = (t_map **)malloc(len_x * len_y * sizeof(t_map *));
	while (y < len_y)
	{
		split = ft_split(non_parsed_map[y], ' ');
		while (split[x])
		{
			final_map[y][x].y = y;
			final_map[y][x].x = x;
			final_map[y][x].z = ft_atoi(ft_split_color(&split[y][x])[0]);
			final_map[y][x].color = ft_atoi_base(ft_split_color(&split[y][x])[1], "abcdef012345");
			
			x++;
		}
		x = 0;
		y++;
	}
	return(final_map);
}

t_map	**map_parser(char *file, int len_height, int len_width)
{
	char	*line;
	char	**map;
	int		fd;
	int		i;

	map = (char **)malloc(len_height * sizeof(char *));
	fd = open(file, O_RDONLY);
	if (!map || fd == -1)
		return (NULL);
	line = get_next_line(fd);
	i = -1;
	while (line)
	{
		map[i] = malloc(ft_strlen(line) * sizeof(char));
		if (!map[i])
		{
			free_parser(line, fd);
			return (free2d(map), NULL);
		}
		map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	free_parser(line, fd);
	return (set_t_point(map, len_height, len_width));
}

int	main(int ac, char **av)
{
	t_map	**map;
	int	len_height;
	int	len_width;

	len_height = len_y(av[1]);
	len_width = len_x(av[1]);
	// void	mlx;
	// void	mlx_win;

	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world");
	map = NULL;
	if (ac != 2)
		return (1);
	map = map_parser(av[1], len_height, len_width);
	display_map(map, len_height, len_width);
	// if (check_errors(map) != 0)
	// 	return (1);
	return (0);
}
