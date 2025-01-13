/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:57:45 by victor-linu       #+#    #+#             */
/*   Updated: 2025/01/13 17:25:56 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*Function that check if a character is a whitespace character*/
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
