/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:24 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/13 17:09:53 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	size_line(char *line)
{
	unsigned int		len_line;
	int					i;

	i = 0;
	len_line = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			while (line[i] == ' ')
				i++;
		else if (ft_isdigit(line[i]) != 0 || line[i] == ','
			|| line[i] == 'x' || line[i] == '\n')
		{
			len_line++;
			while (ft_isdigit(line[i]) != 0 || line[i] == ','
				|| line[i] == 'x' || line[i] == '\n')
				i++;
		}
		else
			return (-1);
	}
	return (len_line);
}

int	check_line_map(char *line, unsigned int len)
{
	unsigned int		len_line;
	int					i;

	len_line = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			while (line[i] == ' ')
				i++;
		else if (ft_isdigit(line[i]) != 0 || line[i] == ','
			|| line[i] == 'x' || line[i] == '\n')
		{
			len_line++;
			while (ft_isdigit(line[i]) != 0 || line[i] == ','
				|| line[i] == 'x' || line[i] == '\n')
				i++;
		}
		else
			return (-1);
	}
	if (len_line != len)
		return (-1);
	return (0);
}

int	check_errors(char **map)
{
	int				i;
	unsigned int	len;

	i = 0;
	len = size_line(map[i]);
	while (map[i])
	{
		if (check_line_map(map[i], len) == -1)
			return (-1);
		i++;
	}
	return (0);
}
