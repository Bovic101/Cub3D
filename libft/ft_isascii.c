/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 04:06:10 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/12 04:46:14 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Test if the input character  belong to the ascii character
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
