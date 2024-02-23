/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:18:18 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/23 19:03:51 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define DATA matrix[0][0]

typedef struct s_map
{
	int		x;
	int		y;
	int		z;
	int		color;
	// int		scale;
	// int		z_scale;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_map;

char	**ft_split_color(char *s);
void	display_tab2d(char **s, int height);
void	free2d(char **str);
void	free_matrix(t_map **matrix);
void	display_matrix(t_map **map, int len_height, int len_width);
void	display_tab2d(char **s, int height);
int		get_height(char *av);
int		get_width(char *line);
char	**line_parser(char *line);
void	fill_matrix(char **line, t_map ***matrix, int width, int *y);
void	set_size_matrix(t_map ***matrix, char *file, int *width, int *height);


#endif
