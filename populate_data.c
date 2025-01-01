/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:32:57 by vodebunm          #+#    #+#             */
/*   Updated: 2024/12/31 17:06:17 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function to initialise the players pos and direction
position the player ti mid of begining grid of the map
*/
void	player_pos_init(t_mlx_render mlx_data)
{
	mlx_data.player->pos_x = (mlx_data.map_data->player_block_x + 0.5)
		* BLOCK_SIZE;
	mlx_data.player->pos_y = (mlx_data.map_data->player_block_y + 0.5)
		* BLOCK_SIZE;
	mlx_data.player->field_view = degree_to_radian(VIEW_ANGLE);
	/*setting the initial player direction to facing down in 2D aray*/
	// mlx_data.player->direction = M_PI; 
}
