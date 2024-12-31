/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:56:20 by vodebunm          #+#    #+#             */
/*   Updated: 2024/05/19 20:51:56 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Function that output a single character  of the string to the standard output
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
