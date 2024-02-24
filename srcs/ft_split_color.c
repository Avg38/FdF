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

char	*extract_first_part(char *s, int *i) {
	int j;
	int k;
	
	j = 0;
	k = 0;
	while (s[j] && s[j] != ',')
		j++;
	char *result = (char *)malloc((j + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (k < j) {
		result[k] = s[k];
		k++;
	}
	result[j] = 0;
	*i = 0;
	while (s[*i] && s[*i] != ',')
		(*i)++;
	(*i) += 2;
	return (result);
}

char	**ft_split_color(char *s)
{
	char	**strs;
	int		i;
	int 	j;

	if (!s)
		return (NULL);
	strs = (char **)malloc(2 * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[0] = extract_first_part(s, &i);
	if (!strs[0])
		return (free(strs), NULL);
	if (ft_strnstr(s, ",0x", 3))
	{
		strs[1] = (char *)malloc((ft_strlen(s) - i + 1) * sizeof(char));
		if (!strs[1])
			return (free2d(strs, 2), NULL);
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


// char **ft_split_color(char *s)
// {
//     char **strs;
//     int i;

//     if (!s)
//         return (NULL);
//     strs = (char **)malloc(2 * sizeof(char *));
//     if (!strs)
//         return (NULL);
//     strs[0] = extract_first_part(s, &i);
//     if (!strs[0])
//         return (free(strs), NULL);
//     if (ft_strnstr(s, ",0x", 3))
//     {
//         strs[1] = (char *)malloc((ft_strlen(s) - i + 1) * sizeof(char));
//         if (!strs[1])
//             return (free(strs[0]), free(strs), NULL);
//         int j = 0;
//         while (s[i])
//         {
//             strs[1][j] = s[i];
//             i++;
//             j++;
//         }
//         strs[1][j] = '\0'; // Ajout du caractère de fin de chaîne
//     }
//     else
//         strs[1] = NULL;
//     return (strs);
// }