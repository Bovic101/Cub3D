/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:32:57 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/12 15:58:34 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function to initialise the players pos and direction
position the player ti mid of begining grid of the map
*/
void player_pos_init(t_mlx_render *mlx_data)
{
    if (!mlx_data || !mlx_data->map_data || !mlx_data->player)
        print_error("Error: Null pointer in player_pos_init\n");

    mlx_data->player->pos_x = (mlx_data->map_data->player_block_x + 0.5) * BLOCK_SIZE;
    mlx_data->player->pos_y = (mlx_data->map_data->player_block_y + 0.5) * BLOCK_SIZE;
    mlx_data->player->field_view = degree_to_radian(VIEW_ANGLE);

    // Default player direction (facing down in the 2D map array)
    mlx_data->player->dir_x = 0.0;
    mlx_data->player->dir_y = 1.0;
}

