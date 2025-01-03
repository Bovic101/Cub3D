/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:22:15 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/03 08:06:09 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

void	texture_input(const char *line_ptr, t_mlx_render *mlx_data)
{
	if (ft_strncmp(line_ptr, "NO", 3) == 0)
	{
		mlx_data->xpm_texture[0] = mlx_load_png(line_ptr + 3);
	}
	else if (ft_strncmp(line_ptr, "SO", 3) == 0)
	{
		mlx_data->xpm_texture[1] = mlx_load_png(line_ptr + 3);
	}
	else if (ft_strncmp(line_ptr, "WE", 3) == 0)
	{
		mlx_data->xpm_texture[2] = mlx_load_png(line_ptr + 3);
	}
	else if (ft_strncmp(line_ptr, "EA", 3) == 0)
	{
		mlx_data->xpm_texture[3] = mlx_load_png(line_ptr + 3);
	}
	else
		print_error("Inalid  texture identifier");
}

/*Function process a line of the map layout fo the cu file & store in  map struct*/
void	map_layout_input(const char *line_ptr, t_map_data *map_data)
{
	if (map_data->map_height >= MAX_MAP_HEIGHT)
	{
		print_error("Error:Maximum height of map reached");
	}
	if (ft_strlen(line_ptr) > MAX_MAP_WIDTH)
	{
		print_error("Error:Maximum width of map reached");
	}
    //Implementation in progress
}
