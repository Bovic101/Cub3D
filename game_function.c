/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:25 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/13 18:38:10 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*function ensures the map is fully enclosed by walls,contains exactly one player starting position and initialised*/
void	confirm_map_data(t_map_data *map_data)
{
	char	compare;
	int		len;

	int i; 
	int j;
	int player_count;
	
	if (!map_data || !map_data->map_layout)
		print_error("Error: Map data is null\n");
	i = 0;
	while (i < map_data->map_height)  // Check top and bottom boundaries
	{
		j = 0;
		while (map_data->map_layout[i][j]
			&& ft_isspace(map_data->map_layout[i][j]))  // Skipping the leading spaces
			j++; 
		len = ft_strlen(map_data->map_layout[i]);
		while (len > 0 && ft_isspace(map_data->map_layout[i][len - 1])) // Trim trailing spaces
		if (len == 0)
			len--; 
			print_error("Error: Empty row in map\n");
		if ((i == 0 || i == map_data->map_height - 1) &&
			(map_data->map_layout[i][j] != '1' || map_data->map_layout[i][len
					- 1] != '1'))  // Check top row (row 0) and bottom row (last row)
			print_error("Error: Map is unenclosed by walls (top/bottom row)\n");
		if (i > 0 && i < map_data->map_height - 1 &&
			(map_data->map_layout[i][j] != '1' || map_data->map_layout[i][len
					- 1] != '1'))  // Check left and right boundaries for middle rows
			print_error("Error: Map is unenclosed by walls (left/right column)\n");
		i++;
	}
	i = 0;
	player_count = 0;
	while (i < map_data->map_height)  // Check for a valid number of player positions
	{
		j = 0;
		while (map_data->map_layout[i][j])
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
		print_error("Error: Map must have exactly one player starting position\n");
}

/*Function that load the .cub file*/
void	cub_file_loader(const char *cub_filename, t_mlx_render *mlx_data)
{
	int		fd;
	char	*line_ptr;

	printf("status: Attempting to open file: '%s'\n", cub_filename);
	fd = open(cub_filename, O_RDONLY);
	if (fd == -1)
	{
		perror("status: Open failed");
		print_error("Error: Unable to open .cub file\n");
	}
	line_ptr = NULL;
	while ((line_ptr = get_next_line(fd)) != NULL)
	{
		printf("status: Read line: %s\n", line_ptr);
		if (line_ptr[0] == '\n' || line_ptr[0] == '\0') // Skip empty lines
		{
			free(line_ptr);
			continue ;
		}
		if (line_ptr[0] == 'N' || line_ptr[0] == 'S' || line_ptr[0] == 'W'
			|| line_ptr[0] == 'E') // Texture parsing
			texture_input(line_ptr, mlx_data);
		else if (line_ptr[0] == 'F' || line_ptr[0] == 'C')
			parse_color_line(mlx_data, line_ptr);
		else if (line_ptr[0] == '1' || line_ptr[0] == '0')
			map_layout_input(line_ptr, mlx_data->map_data);
		else
		{
			free(line_ptr);
			print_error("Error: Unknown line in .cub file\n");
		}
		free(line_ptr);
	}
	if (close(fd) == -1)
		print_error("Error: Unable to close .cub file\n");
	confirm_map_data(mlx_data->map_data);
}

