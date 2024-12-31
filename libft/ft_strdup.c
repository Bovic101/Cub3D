/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:59:49 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/30 00:30:48 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// allocate sufficient memory for a copy of the string
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len_s1;

	len_s1 = ft_strlen(s1) + 1;
	ptr = malloc(len_s1 * sizeof(char));
	if (!ptr)
	{
		return (0);
	}
	ft_memcpy(ptr, s1, len_s1 - 1);
	ptr[len_s1 - 1] = '\0';
	return (ptr);
}
