/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:36:01 by vodebunm          #+#    #+#             */
/*   Updated: 2023/11/02 00:44:48 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// a function to trim a string after passing the desired char
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (set[i] == '\0' || s1[i] == '\0')
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strrchr(set, s1[len - j - 1]))
		j++;
	newstr = ft_substr(s1, i, len - i - j);
	return (newstr);
}

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	size_t	start;
// 	size_t	end;
// 	size_t	new_len;
// 	char	*s2_trim;

// 	if (s1 == NULL || set == NULL)
// 		return (NULL);
// 	start = 0;
// 	end = ft_strlen(s1);
// 	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
// 		start++;
// 	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
// 		end--;
// 	new_len = end - start;
// 	s2_trim = (char *)malloc(new_len + 1);
// 	if (s2_trim == NULL)
// 	{
// 		return (NULL);
// 	}
// 	strncpy(s2_trim, s1 + start, new_len);
// 	s2_trim[new_len] = '\0';
// 	return (s2_trim);
// }
