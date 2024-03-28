/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:24 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 16:05:38 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	close_win(t_matrix **matrix)
{
	mlx_destroy_image(matrix[0][0].mlx, matrix[0][0].imgs.img);
	mlx_destroy_window(matrix[0][0].mlx, matrix[0][0].win);
	mlx_destroy_display(matrix[0][0].mlx);
	free(matrix[0][0].mlx);
	free_matrix(matrix, matrix[0][0].height);
	exit (EXIT_SUCCESS);
	return (0);
}

int	esc_handler(int key, t_matrix **matrix)
{
	if (key == 65307)
		close_win(matrix);
	return (0);
}

void	ft_exit(char *msg, t_matrix **matrix, int height)
{
	if (matrix)
		free_matrix(matrix, height);
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	free_2d(char **str, int len)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i < len)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	free_matrix(t_matrix **matrix, int height)
{
	int	y;

	y = 0;
	if (!matrix)
		return ;
	while (y < height)
	{
		free(matrix[y]);
		y++;
	}
	free(matrix);
}
