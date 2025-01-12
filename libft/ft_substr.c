/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 03:02:16 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/30 15:17:24 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// used to extract a substring from a string
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*s2;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (len >= size - start)
		len = size - start;
	if (start >= size)
		return (ft_strdup(""));
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s[start];
		i++;
		start++;
	}
	s2[i] = '\0';
	return (s2);
}
