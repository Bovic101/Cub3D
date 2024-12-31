/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:33:01 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/30 00:25:20 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// search for char in a string and returns a pointer of the last occurence 
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*result;

	result = (char *)s;
	i = ft_strlen(result);
	while (i != -1)
	{
		if (result[i] == (char)c)
			return (result + i);
		i--;
	}
	return (NULL);
}
