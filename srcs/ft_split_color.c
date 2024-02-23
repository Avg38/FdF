/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:15:17 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/23 19:08:07 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

char	**alloc_split_color(char **strs, char *s, int *i)
{
	strs = (char **)malloc(2 * sizeof(char *));
	if (!strs)
		return (NULL);
	while (s[*i] && s[*i] != ',')
		(*i)++;
	strs[0] = (char *)malloc((*i + 1) * sizeof(char));
	if (!strs[0])
		return (free(strs), NULL);
	strs[0][*i + 1] = 0;
	*i = 0;
	while (s[*i] && s[*i] != ',')
	{
		strs[0][*i] = s[*i];
		(*i)++;
	}
	return (strs);
}

char	**ft_split_color(char *s)
{
	char	**strs;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	strs = NULL;
	strs = alloc_split_color(strs, s, &i);
	if (!strs)
		return (NULL);
	if (ft_strnstr(s, ",0x", 3))
	{
		strs[1] = (char *)malloc(7 * sizeof(char));
		if (!strs[1])
			return (free2d(strs), NULL);
		strs[1][6] = 0;
		i += 2;
		while (s[++i])
			strs[1][i - 4] = s[i];
	}
	else
		strs[1] = NULL;
	return (strs);
}
