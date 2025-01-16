/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:22:15 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/16 18:23:21 by taha             ###   ########.fr       */
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
	if (access(texture_path, R_OK) == -1)
	{
		perror("Error: Failed to access texture file");
		print_error("Error: Texture file does not exist or is not readable\n");
	}
	*texture_pos = mlx_load_png(texture_path);
	if (!(*texture_pos))
		print_error("Error: Failed to load texture\n");
	printf("Status: Successfully loaded texture: '%s'\n", texture_path);
}

/*Function parse and load textures using the texture_loader and texture_path-parser function*/

void texture_input(const char *line_ptr, t_mlx_render *mlx_data)
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
	size_t	line_length;

	line_length = ft_strlen(line_ptr);
	if (!map_data)
		print_error("Error: Null map_data in map_layout_input\n");
	if (!map_data->map_layout)
	{
		map_data->allocated_height = MAX_MAP_HEIGHT;
		map_data->map_layout = malloc(map_data->allocated_height
				* sizeof(char *));
		if (!map_data->map_layout)
			print_error("Error: Memory allocation failed for map layout\n");
	}
	if (map_data->map_height >= map_data->allocated_height)
	{
		map_data->allocated_height *= 2;
		map_data->map_layout = realloc(map_data->map_layout,
										map_data->allocated_height
											* sizeof(char *));
		if (!map_data->map_layout)
			print_error("Error: Memory allocation failed during map reallocation\n");
	}
	map_data->map_layout[map_data->map_height] = malloc(line_length + 1);
	if (!map_data->map_layout[map_data->map_height])
		print_error("Error: Memory allocation failed for map row\n");
	ft_strncpy(map_data->map_layout[map_data->map_height], line_ptr,
			line_length);
	map_data->map_layout[map_data->map_height][line_length] = '\0';
	map_data->map_height++;
}

void	parse_color_line(t_mlx_render *mlx_data, const char *line)
{
	if (line[0] == 'F')
		mlx_data->floor_c = parse_color(line); //strore parse floor color
	else if (line[0] == 'C')
		mlx_data->ceiling_c = parse_color(line);
}

void	read_colors(const char *file_path, t_mlx_render *mlx_data)
{
	int		fd;
	char	*line;

	if (!file_path || !mlx_data)
		print_error("Error: Invalid arguments passed to read_colors\n");
	printf("status: Opening file for reading colors: '%s'\n", file_path);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("status: Open failed");
		print_error("Error: Unable to open .cub file for reading colors\n");
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("status: Read line: %s\n", line);
		if (line[0] == 'F' || line[0] == 'C')
			parse_color_line(mlx_data, line);
		free(line);
	}
	if (close(fd) == -1)
		print_error("Error: Unable to close .cub file after reading colors\n");
}