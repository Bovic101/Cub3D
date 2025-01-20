/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:32:57 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/20 02:10:55 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function to initialise the players pos and direction
position the player ti mid of begining grid of the map
*/
void	player_pos_init(t_mlx_render *mlx_data)
{
	mlx_data->player->pos_x = (mlx_data->map_data->player_block_x + 0.5)
		* BLOCK_SIZE;
	mlx_data->player->pos_y = (mlx_data->map_data->player_block_y + 0.5)
		* BLOCK_SIZE;
	mlx_data->player->dir_x = 0;
	mlx_data->player->dir_y = -1;
	mlx_data->player->plane_x = 0.66;
	mlx_data->player->plane_y = 0;
	mlx_data->player->m_up = 0;
	mlx_data->player->m_down = 0;
	mlx_data->player->m_left = 0;
	mlx_data->player->m_right = 0;
	mlx_data->player->p_rot = 0;
}
