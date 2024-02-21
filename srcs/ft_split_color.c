/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:15:17 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/21 13:47:40 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

char	**ft_split_color(char *s)
{
	char	**strs;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	strs = (char **)malloc(2 * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	if (strnstr(s, ",0x", 3))
	{
		while (s[i] != ',')
			i++;
		strs[0] = (char *)malloc((i + 1) * sizeof(char));
		strs[1] = (char *)malloc(7 * sizeof(char));
		if (!strs[0] || !strs[1])
			return (NULL);
		strs[0][i + 1] = 0;
		strs[1][6] = 0;
		i = -1;
		while (s[++i] != ',')
			strs[0][i] = s[i];
		i += 2;
		while (s[++i])
			strs[1][i - 4] = s[i];
	}
	return (strs);
}
