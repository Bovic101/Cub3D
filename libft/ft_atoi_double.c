/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 05:14:02 by vodebunm          #+#    #+#             */
/*   Updated: 2024/07/21 15:04:44 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atoi_double(const char *str)
{
	int		i;
	int		sign;
	double	result;
	double	fraction;
	double	divisor;

	i = 0;
	sign = 1;
	result = 0.0;
	fraction = 0.0;
	divisor = 1.0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			fraction = (str[i] - '0') + (fraction * 10);
			divisor *= 10;
			i++;
		}
		result += fraction / divisor;
	}
	return (result * sign);
}
