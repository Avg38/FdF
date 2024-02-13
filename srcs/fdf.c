/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/13 17:19:55 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

void	display_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s", map[i]);
		i++;
	}
}

char	**map_parser(char *av)
{
	char	*line;
	char	**map;
	int		fd;
	int		i;

	map = (char **)malloc(MAX_LINES * sizeof(char *));
	fd = open(av, O_RDONLY);
	if (!map || fd == -1)
		return (NULL);
	line = get_next_line(fd);
	i = -1;
	while (line && ++i < MAX_LINES)
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
	return (map);
}

int	main(int ac, char **av)
{
	char	**map;

	if (ac != 2)
		return (1);
	map = map_parser(av[1]);
	display_map(map);
	if (check_errors(map) != 0)
		return (1);
	return (0);
}
