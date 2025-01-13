/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:22:15 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/13 13:47:28 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function extractthe file path of a tecture from the config file(.cub flie) line*/
char	*texture_path_parser(const char *line_ptr)
{
	char	*path;
	size_t	len;

	path = NULL;
	if (ft_strncmp(line_ptr, "NO ", 3) == 0 ||
		ft_strncmp(line_ptr, "SO ", 3) == 0 ||
		ft_strncmp(line_ptr, "WE ", 3) == 0 ||
		ft_strncmp(line_ptr, "EA ", 3) == 0)
	{
		path = ft_strdup(line_ptr + 3); // Duplicate the path
		if (!path)
			print_error("Error: Memory allocation failed for texture path\n");
		len = ft_strlen(path);
		while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' '))
		// Trim whitespace and newlines
		{
			path[len - 1] = '\0';
			len--;
		}
		return (path);
	}
	print_error("Error: Invalid texture identifier\n");
	return (NULL);
}

/*Function that load texture into the exact position in the texture array as declared in the header*/
void	texture_loader(const char *texture_path, mlx_texture_t **texture_pos)
{
	if (!texture_path || !texture_pos)
		print_error("Error: Invalid arguments in texture_loader\n");
	printf("status: Checking texture path: '%s'\n", texture_path);
	if (access(texture_path, R_OK) == -1)
	{
		perror("Debug: Texture file access failed");
		print_error("Error: Texture file does not exist or is not readable\n");
			// Check if the texture file exists and is readable
	}
	*texture_pos = mlx_load_png(texture_path); // Load the texture
	if (!(*texture_pos))
	{
		print_error("Error: Failed to load texture\n");
	}
	printf("status: Successfully loaded texture: '%s'\n", texture_path);
}

/*Function parse and load textures using the texture_loader and texture_path-parser function*/
void	texture_input(const char *line_ptr, t_mlx_render *mlx_data)
{
	char	*texture_path;
	int		texture_index;

	texture_index = -1;
	if (ft_strncmp(line_ptr, "NO ", 3) == 0)
		texture_index = 0;
	else if (ft_strncmp(line_ptr, "SO ", 3) == 0)
		texture_index = 1;
	else if (ft_strncmp(line_ptr, "WE ", 3) == 0)
		texture_index = 2;
	else if (ft_strncmp(line_ptr, "EA ", 3) == 0)
		texture_index = 3;
	if (texture_index == -1)
		print_error("Error: Invalid texture identifier\n");
	texture_path = texture_path_parser(line_ptr);
	if (!texture_path)
		print_error("Error: Failed to parse texture path\n");
	texture_loader(texture_path, &mlx_data->xpm_texture[texture_index]);
	free(texture_path);
}

/*Function that read map line in the cub and stores it in the 2D array rep. d map*/
void	map_layout_input(const char *line_ptr, t_map_data *map_data)
{
	if (!map_data)
		print_error("Error: Null map_data in map_layout_input\n");
	if (map_data->map_height >= MAX_MAP_HEIGHT)
		print_error("Error: Maximum map height exceeded\n");
	if (ft_strlen(line_ptr) > MAX_MAP_WIDTH)
		print_error("Error: Maximum map width exceeded\n");
	if (!map_data->map_layout)
	{
		map_data->map_layout = malloc(MAX_MAP_HEIGHT * sizeof(char *));
		if (!map_data->map_layout)
			print_error("Error: Memory allocation failed for map layout\n");
	}
	map_data->map_layout[map_data->map_height] = malloc(MAX_MAP_WIDTH + 1);
	if (!map_data->map_layout[map_data->map_height])
		print_error("Error: Memory allocation failed for map row\n");
	strncpy(map_data->map_layout[map_data->map_height], line_ptr,
			MAX_MAP_WIDTH);
	map_data->map_layout[map_data->map_height][MAX_MAP_WIDTH] = '\0';
	// Null-terminate
	map_data->map_height++;
}

void	confirm_map_data(t_map_data *map_data)
{
	int		i;
	int		j;
	int		player_count;
	char	compare;

	if (!map_data || !map_data->map_layout)
		print_error("Error: Map data is null\n");
	i = 0;
	j = 0;
	while (j < map_data->map_width)
	// Checking boundaries for walls(top& bottom)
	{
		if (map_data->map_layout[0][j] != '1' ||
			map_data->map_layout[map_data->map_height - 1][j] != '1')
			print_error("Error: Map is unnclosed by walls\n");
		j++;
	}
	while (i < map_data->map_height)
	// Checking boundaries for walls(left& right)
	{
		if (map_data->map_layout[i][0] != '1' ||
			map_data->map_layout[i][map_data->map_width - 1] != '1')
			print_error("Error: Map is unenclosed by walls\n");
		i++;
	}
	i = 0; //reset for next loop
	player_count = 0;
	while (i < map_data->map_height)
	// Checking for a valid number of player positions
	{
		j = 0;
		while (j < map_data->map_width)
		{
			compare = map_data->map_layout[i][j];
			if (compare == 'N' || compare == 'S' || compare == 'E'
				|| compare == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		print_error("Error: Map must have one player starting position\n");
}
