/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 01:36:22 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/25 02:21:41 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// erases byte in the memory locations and start them to zero
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
