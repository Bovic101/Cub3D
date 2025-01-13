/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:22:15 by vodebunm          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/12 17:01:54 by victor-linu      ###   ########.fr       */
=======
/*   Updated: 2025/01/13 17:18:57 by victor-linu      ###   ########.fr       */
>>>>>>> d3b55e6 (implementationa anbd addition of function function ensures the map is fully enclosed by walls,contains exactly one player starting position)
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function extractthe file path of a tecture from the config file(.cub flie) line*/
char *texture_path_parser(const char *line_ptr)
{
<<<<<<< HEAD
    char *path = NULL;

    if (ft_strncmp(line_ptr, "NO ", 3) == 0 ||
        ft_strncmp(line_ptr, "SO ", 3) == 0 ||
        ft_strncmp(line_ptr, "WE ", 3) == 0 ||
        ft_strncmp(line_ptr, "EA ", 3) == 0)
    {
        path = ft_strdup(line_ptr + 3); // Duplicate the path
        if (!path)
            print_error("Error: Memory allocation failed for texture path\n");

        size_t len = ft_strlen(path);
        while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' ')) // Trim whitespace and newlines
        {
            path[len - 1] = '\0';
            len--;
        }
        return path;
    }

    print_error("Error: Invalid texture identifier\n");
    return NULL;
=======
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
		while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' '))  // Trim whitespace and newlines
		{
			path[len - 1] = '\0';
			len--;
		}
		return (path);
	}
	print_error("Error: Invalid texture identifier\n");
	return (NULL);
>>>>>>> d3b55e6 (implementationa anbd addition of function function ensures the map is fully enclosed by walls,contains exactly one player starting position)
}

/*Function that load texture into the exact position in the texture array as declared in the header*/
void	texture_loader(const char *texture_path, mlx_texture_t **texture_pos)
{
<<<<<<< HEAD
    if (!texture_path || !texture_pos)
        print_error("Error: Invalid arguments in texture_loader\n");

    printf("status: Checking texture path: '%s'\n", texture_path);

    if (access(texture_path, R_OK) == -1)  // Check if the texture file exists and is readable
    {
        perror("Debug: Texture file access failed");
        print_error("Error: Texture file does not exist or is not readable\n");
    }

    *texture_pos = mlx_load_png(texture_path);  // Load the texture
    if (!(*texture_pos))
    {
        print_error("Error: Failed to load texture\n");
    }
    printf("status: Successfully loaded texture: '%s'\n", texture_path);
}



=======
	if (!texture_path || !texture_pos)
		print_error("Error: Invalid arguments in texture_loader\n");
	printf("status: Checking texture path: '%s'\n", texture_path);
	if (access(texture_path, R_OK) == -1)
	{
		perror("Debug: Texture file access failed");
		print_error("Error: Texture file does not exist or is not readable\n");  // Check if the texture file exists and is readable
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

    strncpy(map_data->map_layout[map_data->map_height], line_ptr, MAX_MAP_WIDTH);
    map_data->map_layout[map_data->map_height][MAX_MAP_WIDTH] = '\0'; // Null-terminate
    map_data->map_height++;
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
	ft_strncpy(map_data->map_layout[map_data->map_height], line_ptr,
			MAX_MAP_WIDTH);
	map_data->map_layout[map_data->map_height][MAX_MAP_WIDTH] = '\0';
		// Null-terminate
	map_data->map_height++;
}


