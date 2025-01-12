/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:11:08 by vodebunm          #+#    #+#             */
/*   Updated: 2023/11/01 12:23:51 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//Output a string to the S/O followed by a new line
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
