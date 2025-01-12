/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:33:41 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/27 18:46:50 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// This function is used to assign a specific value to a memory block
void	*ft_memset(void *s, int c, size_t length)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (length != 0)
	{
		*str = (unsigned char)c;
		str++;
		length--;
	}
	return (s);
}
