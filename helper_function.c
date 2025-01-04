/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:50 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/04 12:01:36 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"
/*Function to converts an angle given in degrees into its equivalent in radian*/
double	degree_to_radian(double value)
{
	return (value * M_PI / 180.0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;

	if (n == 0)
		return (0);
	i = 0;
	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	if (i >= n)
		i--;
	return (s1[i] - s2[i]);
}
 void print_error(const char *string)
 {
	perror(string);
	exit(EXIT_FAILURE);
 }
