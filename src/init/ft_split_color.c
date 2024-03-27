/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:15:17 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 16:30:01 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

char	**extract_first_part(char *s, int *i)
{
	int		j;
	int		k;
	char	**strs;

	strs = (char **)malloc(2 * sizeof(char *));
	if (!strs)
		return (NULL);
	j = 0;
	k = -1;
	while (s[j] && s[j] != ',')
		j++;
	strs[0] = (char *)malloc((j + 1) * sizeof(char));
	if (!strs[0])
		return (NULL);
	while (++k < j)
		strs[0][k] = s[k];
	strs[0][j] = 0;
	*i = 0;
	while (s[*i] && s[*i] != ',')
		(*i)++;
	(*i) += 2;
	return (strs);
}

char	**ft_split_color(char *s)
{
	char	**strs;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	strs = extract_first_part(s, &i);
	if (!strs || !strs[0])
		return (free_2d(strs, 1), NULL);
	if (ft_strnstr(s, ",0x", 3))
	{
		strs[1] = (char *)malloc((ft_strlen(s) - i + 1) * sizeof(char));
		if (!strs[1])
			return (free_2d(strs, 2), NULL);
		j = 0;
		while (s[++i])
		{
			strs[1][j] = s[i];
			j++;
		}
		strs[1][j] = 0;
	}
	else
		strs[1] = NULL;
	return (strs);
}
