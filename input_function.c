/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:22:15 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/08 01:33:55 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"
/*Function extractthe file path of a tecture from the config file(.cub flie) line*/
char	*texture_path_parser(const char *line_ptr)
{
	if (ft_strncmp(line_ptr, "NO ", 3) == 0)
	{
		return(ft_strdup(line_ptr + 3));
	}
	else if (ft_strncmp(line_ptr, "SO ", 3) == 0)
	{
		return(ft_strdup(line_ptr + 3));
	}
	else if (ft_strncmp(line_ptr, "WE ", 3) == 0)
	{
		return(ft_strdup(line_ptr + 3));
	}
	else if (ft_strncmp(line_ptr, "EA ", 3) == 0)
	{
		return(ft_strdup(line_ptr + 3));
	}
	else
		print_error("Inalid  texture identifier\n");
	return(NULL);
}
/*Function that load texture into the exact position in the texture array as declared in the header*/
void texture_loader(const char *texture_path, mlx_texture_t **texture_pos)
{
	*texture_pos = mlx_load_png(texture_path);
	if (!texture_pos)
	{
		print_error("Error: Loading texture failed\n");
	}
}
/*Function parse and load textures using the texture_loader and texture_path-parser function*/
void	texture_input(const char *line_ptr, t_mlx_render *mlx_data)
{
	char *texture_path = texture_path_parser(line_ptr); //this parse the texture path
	
	if (ft_strncmp(line_ptr, "NO ", 3) == 0)
	{
		texture_loader(texture_path, &mlx_data->xpm_texture[0]);
	}
	else if (ft_strncmp(line_ptr, "SO ", 3) == 0)
	{
		texture_loader(texture_path, &mlx_data->xpm_texture[1]);
	}
	else if (ft_strncmp(line_ptr, "WE ", 3) == 0)
	{
		texture_loader(texture_path, &mlx_data->xpm_texture[2]);
	}
	else if (ft_strncmp(line_ptr, "EA ", 3) == 0)
	{
		texture_loader(texture_path, &mlx_data->xpm_texture[3]);
	}
	free(texture_path);
}


/*Function that read map line in the cub and stores it in the 2D array rep. d map*/
void	map_layout_input(const char *line_ptr, t_map_data *map_data)
{
	if (map_data->map_height >= MAX_MAP_HEIGHT)
	{
		print_error("Error:Maximum height of map reached\n");
	}
	if (ft_strlen(line_ptr) > MAX_MAP_WIDTH)
	{
		print_error("Error:Maximum width of map reached\n");
	}
	if (!map_data->map_layout)
	{
		map_data->map_layout = malloc(MAX_MAP_HEIGHT * sizeof(char *));
		if (!map_data->map_layout)
		{
			print_error("Error:Map layout memory allocaction failure\n");
		}
	}
	map_data->map_layout[map_data->map_height] = malloc(MAX_MAP_WIDTH + 1);
	if (!map_data->map_layout[map_data->map_height])
	{
		print_error("Error: Map row memory allocation failed\n");
	}
	//strncpy();//implemetation uncompleted
}
