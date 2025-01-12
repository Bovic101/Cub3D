/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:25:22 by vodebunm          #+#    #+#             */
/*   Updated: 2023/10/12 01:58:24 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Test for decimal digit character("0-9")
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
