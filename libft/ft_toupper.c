/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 05:12:36 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/12 05:47:11 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function used to convert a lower-case letter to uppercas

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = c - 32;
	}
	return (c);
}
