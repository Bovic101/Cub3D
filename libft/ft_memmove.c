/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:47:33 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/26 19:49:11 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// use to copy byte from one location in the memory to another
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst == src)
	{
		return (dst);
	}
	if (source < dest)
	{
		while (len--)
		{
			dest[len] = source[len];
		}
	}
	else
	{
		while (len--)
		{
			*dest++ = *source++;
		}
	}
	return (dst);
}
