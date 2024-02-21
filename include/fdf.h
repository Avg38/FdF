/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:18:18 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/21 15:29:11 by avialle-         ###   ########.fr       */
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


#endif
