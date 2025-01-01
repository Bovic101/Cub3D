/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:35:05 by taha              #+#    #+#             */
/*   Updated: 2024/12/31 17:03:56 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cup3d.h"
#include <stdio.h>
#include <stdlib.h>

void	init_window(t_game *game)
{
	game->mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cup3d", false);
	game->screen = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	// if (game->screen) gonna add terminate and clean

	if (mlx_image_to_window(game->mlx, game->screen, 0, 0) < 0)
	{
		//del image
		// terminate
		//return
	}
	return (1);
}
void	init_player(t_game *game)
{
	game->p->pos_x = 0;
	game->p->pos_y = 0;
	game->p->dir_x = -1;
	game->p->dir_y = 0;
	game->p->plane_x = 0;
	game->p->plane_y = 0.66;
	game->p->p_rot = TURNING_SPEED;
	game->p->p_speed = PLAYER_MOVE_SPEED;

}

void	init_game(t_game *game)
{
	init_window(game);
	init_player(game);
}

int	main(void)
{
	t_game *game;

	init_game(game);
	mlx_loop(game->mlx);
}
