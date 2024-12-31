/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:43:06 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/08 15:49:13 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void handle_error(const char *str)
{
    printf("Error occurred: %s\n", str);
    exit(EXIT_FAILURE);
}

static inline bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

const char *acceptable_input(const char *str)
{
    int length = 0;
    const char *nbr;

    if (str == NULL)  // Ensure the input string is not null
    {
        handle_error("Input string is null");
    }

    while ((*str >= 9 && *str <= 13) || *str == 32)  // Skip white spaces
    {
        str++;
    }
    if (*str == '+')
    {
        str++;
    }
    else if (*str == '-')
    {
        handle_error("Negative value not allowed");
    }
    if (!is_digit(*str))
    {
        handle_error("The digit is not within the acceptable range");
    }

    nbr = str;
    while (is_digit(*str))
    {
        length++;
        str++;
    }

    if (length > 10)
    {
        handle_error("Digit range is beyond acceptable limit");
    }

    return nbr;  // Return the pointer to the start of the number
}

long ft_atol(const char *str)
{
    long nbr = 0;

    str = acceptable_input(str);
    while (is_digit(*str))
    {
        nbr = (nbr * 10) + (*str++ - '0');
    }

    if (nbr > INT_MAX)
    {
        handle_error("Digit range is beyond acceptable limit");
    }

    return nbr;
}