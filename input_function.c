/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:22:15 by vodebunm          #+#    #+#             */
/*   Updated: 2024/12/31 02:15:25 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

void	texture_input(const char *line_ptr, t_mlx_render *mlx_data)
{
	if (ft_strncmp(line_ptr, "NO", 3) == 0)
	{
		mlx_data->xpm_texture[0] = mlx_load_xpm42(line_ptr + 3);
	}
	else if (ft_strncmp(line_ptr, "SO", 3) == 0)
	{
		mlx_data->xpm_texture[1] = mlx_load_xpm42(line_ptr + 3);
	}
	else if (ft_strncmp(line_ptr, "WE", 3) == 0)
	{
		mlx_data->xpm_texture[2] = mlx_load_xpm42(line_ptr + 3);
	}
	else if (ft_strncmp(line_ptr, "EA", 3) == 0)
	{
		mlx_data->xpm_texture[3] = mlx_load_xpm42(line_ptr + 3);
	}
	else
		print_error("Inalid  texture identifier");
}
