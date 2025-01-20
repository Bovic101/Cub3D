/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:25 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/20 12:46:04 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

void	check_map_character(t_map_data *map_data, int i, int *player_count)
{
	size_t	j;
	char	c;

	j = 0;
	while (j < ft_strlen(map_data->map_layout[i]))
	{
		c = map_data->map_layout[i][j];
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			map_data->player_block_x = j;
			map_data->player_block_y = i;
			(*player_count)++;
			printf("status: Player found at (%d, %zu)\n", i, j);
		}
		else if (c != '1' && c != '0' && c != ' ')
		{
			printf("status: Invalid character '%c' at (%d, %zu)\n", c, i, j);
			print_error("Error: Invalid character in map\n");
		}
		if (c == ' ' && !is_surrounded_by_walls(map_data, i, j))
			print_error("Error: Space inside map not enclosed by walls\n");
		j++;
	}
}

void	confirm_map_data(t_map_data *map_data)
{
	int	i;
	int	player_count;

	i = 0;
	player_count = 0;
	if (!map_data || !map_data->map_layout)
		print_error("Error: Map data is null\n");
	while (i < map_data->map_height)
	{
		check_map_character(map_data, i, &player_count);
		i++;
	}
	printf("status: Total player positions found: %d\n", player_count);
	if (player_count != 1)
		print_error("Error: Map must have exactly one player at start\n");
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
	int	i;

	i = 0;
	printf("status: Parsed Map Layout:\n");
	while (i < map_data->map_height)
	{
		printf("%s\n", map_data->map_layout[i]);
		i++;
	}
}
