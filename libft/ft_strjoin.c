/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:12:31 by vodebunm          #+#    #+#             */
/*   Updated: 2023/11/02 00:56:00 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that return a new str as a result of merge of str1 and str2

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (!result || !s1 || !s2)
		return (NULL);
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < len2 + len1)
	{
		result[i] = *s2;
		i++;
		s2++;
	}
	result[i] = '\0';
	return (result);
}
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		len1;
// 	int		len2;

// 	int		total_length;
// 	char	*s3;

// 	if (s1 == NULL || s2 == NULL)
// 	{
// 		return (NULL);
// 	}
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	total_length = len1 + len2;
// 	s3 = (char *)malloc(total_length + 1);
// 	if (s3)
// 	{
// 		strcpy(s3, s1);
// 		strcat(s3, s2);
// 	}
// 	return (s3);
// }
