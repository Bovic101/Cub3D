/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:44:44 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/30 00:27:35 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copy a block of memory from the source location to destination location
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest && !src)
	{
		return (dest);
	}
	d = dest;
	s = src;
	while (n)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}
