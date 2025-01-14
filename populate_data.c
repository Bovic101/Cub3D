/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:32:57 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/14 19:25:20 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function to initialise the players pos and direction
position the player ti mid of begining grid of the map
*/
void	player_pos_init(t_mlx_render *mlx_data)
{
	if (!mlx_data || !mlx_data->map_data || !mlx_data->player)
		print_error("Error: Null pointer in player_pos_init\n");
	mlx_data->player->pos_x = (mlx_data->map_data->player_block_x + 0.5)
		* BLOCK_SIZE; // Set player position to the middle of the block
	mlx_data->player->pos_y = (mlx_data->map_data->player_block_y + 0.5)
		* BLOCK_SIZE;
	char player_dir = mlx_data->map_data->map_layout[mlx_data->map_data->player_block_y][mlx_data->map_data->player_block_x];
		// Set default direction based on player symbol (N, S, E, W)
	if (player_dir == 'N')
	{
		mlx_data->player->dir_x = 0;
		mlx_data->player->dir_y = -1;
	}
	else if (player_dir == 'S')
	{
		mlx_data->player->dir_x = 0;
		mlx_data->player->dir_y = 1;
	}
	else if (player_dir == 'E')
	{
		mlx_data->player->dir_x = 1;
		mlx_data->player->dir_y = 0;
	}
	else if (player_dir == 'W')
	{
		mlx_data->player->dir_x = -1;
		mlx_data->player->dir_y = 0;
	}
	mlx_data->player->plane_x = mlx_data->player->dir_y * 0.66;
		// Initialize the camera plane for FOV
	mlx_data->player->plane_y = -mlx_data->player->dir_x * 0.66;
	printf("status: Player initialized at (%d, %d) facing (%.2f, %.2f)\n",
			mlx_data->player->pos_x,
			mlx_data->player->pos_y,
			mlx_data->player->dir_x,
			mlx_data->player->dir_y);
}
