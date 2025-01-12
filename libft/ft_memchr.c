/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:03:45 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/26 16:47:47 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function use to scan memory a specified character
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	value;

	s1 = (unsigned char *)s;
	value = (unsigned char)c;
	if (n == 0)
	{
		return (NULL);
	}
	while (n)
	{
		if (*s1 == value)
		{
			return (s1);
		}
		s1++;
		n--;
	}
	return (NULL);
}
