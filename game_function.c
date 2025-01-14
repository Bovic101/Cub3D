/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:25 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/14 19:05:08 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

void	confirm_map_data(t_map_data *map_data)
{
	char	c;
	size_t	j;

	int i, player_count = 0;
	if (!map_data || !map_data->map_layout)
		print_error("Error: Map data is null\n");
	for (i = 0; i < map_data->map_height; i++)
	{
		for (j = 0; j < ft_strlen(map_data->map_layout[i]); j++)
		{
			c = map_data->map_layout[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				map_data->player_block_x = j;
				map_data->player_block_y = i;
				player_count++;
				printf("status: Player found at (%d, %zu)\n", i, j);
			}
			else if (c != '1' && c != '0' && c != ' ')
			{
				printf("status: Invalid character '%c' at (%d, %zu)\n", c, i,
						j);
				print_error("Error: Invalid character in map\n");
			}
			if (c == ' ' && !is_surrounded_by_walls(map_data, i, j))
				// Ensure spaces are properly enclosed by walls
				print_error("Error: Space inside map not enclosed by walls\n");
		}
	}
	printf("status: Total player positions found: %d\n", player_count);
	if (player_count != 1)
		print_error("Error: Map must have exactly one player starting position\n");
}

int	is_surrounded_by_walls(t_map_data *map_data, int i, int j)
{
	if (i <= 0 || i >= map_data->map_height - 1 || j <= 0
		|| j >= map_data->map_width - 1)
		return (0);
	if (map_data->map_layout[i - 1][j] != '1' && map_data->map_layout[i
		- 1][j] != ' ')
		return (0);
	if (map_data->map_layout[i + 1][j] != '1' && map_data->map_layout[i
		+ 1][j] != ' ')
		return (0);
	if (map_data->map_layout[i][j - 1] != '1' && map_data->map_layout[i][j
		- 1] != ' ')
		return (0);
	if (map_data->map_layout[i][j + 1] != '1' && map_data->map_layout[i][j
		+ 1] != ' ')
		return (0);
	return (1);
}
/*Function to debug map layout*/
void	debug_print_map(t_map_data *map_data)
{
	printf("status: Parsed Map Layout:\n");
	for (int i = 0; i < map_data->map_height; i++)
	{
		printf("%s\n", map_data->map_layout[i]);
	}
}

/*Function that load the .cub file*/
void	cub_file_loader(const char *cub_filename, t_mlx_render *mlx_data)
{
	int		fd;
	char	*line_ptr;
	char	*trimmed_line;

	printf("status:Opening file: '%s'\n", cub_filename);
	fd = open(cub_filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: Failed to open .cub file");
		print_error("Error: Unable to open .cub file\n");
	}
	line_ptr = NULL;
	while ((line_ptr = get_next_line(fd)) != NULL)
	{
		trimmed_line = ft_strtrim(line_ptr, " \n\t\r");  // Trim leading/trailing spaces for cleaner data processing
		if (trimmed_line[0] == '\0')  // Skip empty lines
		{
			free(trimmed_line);
			free(line_ptr);
			continue ;
		}
		printf("status: Processing line: '%s'\n", trimmed_line);
		if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line,
				"SO ", 3) == 0 ||
			ft_strncmp(trimmed_line, "WE ", 3) == 0 || ft_strncmp(trimmed_line,
					"EA ", 3) == 0)
		{
			texture_input(trimmed_line, mlx_data);
		}
		else if (ft_strncmp(trimmed_line, "F ", 2) == 0
				|| ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			parse_color_line(mlx_data, trimmed_line); // Parse floor/ceiling colors
		}
		else if (trimmed_line[0] == '1' || trimmed_line[0] == '0')
		{
			map_layout_input(trimmed_line, mlx_data->map_data);
		}
		else
		{
			free(trimmed_line);
			free(line_ptr);
			print_error("Error: Unknown or invalid line in .cub file\n");
		}
		free(trimmed_line);
		free(line_ptr);
	}
	if (close(fd) == -1)
		print_error("Error: Unable to close .cub file\n");
	confirm_map_data(mlx_data->map_data);  // Validate the map data after parsing
	debug_print_map(mlx_data->map_data);  //Print parsed map outputr
}
