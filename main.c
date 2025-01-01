/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:35:05 by taha              #+#    #+#             */
/*   Updated: 2025/01/01 14:01:21 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cup3d.h"
#include <stdio.h>
#include <stdlib.h>

static void	init_window(t_game *game)
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
static void	init_player(t_game *game)
{
	game->p->pos_x = 0;
	game->p->pos_y = 0;
	game->p->dir_x = -1;
	game->p->dir_y = 0;
	game->p->plane_x = 0;
	game->p->plane_y = 0.66;
	game->p->p_rot = TURNING_SPEED;
	game->p->p_speed = PLAYER_MOVE_SPEED;
	game->p->m_down = 0; // gs
	game->p->m_up = 0; // gs
	game->p->m_left = 0; // gs
	game->p->m_right = 0; // gs
	game->p->field_view = VIEW_ANGLE;
}

void	init_game(t_game *game)
{
	init_window(game);
	init_player(game);
}

static void key_handler(mlx_key_data_t keydata, void *param)
{
	t_game *game = (t_game *)param;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->p->m_down = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->p->m_up = 1;
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S) && keydata.action == MLX_RELEASE)
	{
		game->p->m_down = 0;
		game->p->m_up = 0;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->p->m_left = 1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->p->m_right = 1;
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D) && keydata.action == MLX_RELEASE)
	{
		game->p->m_right = 0;
		game->p->m_left = 0;
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->p->p_rot = -TURNING_SPEED;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->p->p_rot = TURNING_SPEED;
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT) && keydata.action == MLX_RELEASE)
		game->p->p_rot = 0;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}


static void move_player(t_game *game)
{
	double move_speed = PLAYER_MOVE_SPEED;
	double rot_speed = TURNING_SPEED;
	double old_dir_x; 		// gonna find way to decrease variable number. maybe gonna add to strcutures
	double old_dir_y; 		// gonna find way to decrease variable number. maybe gonna add to strcutures
	double old_plane_x;		// gonna find way to decrease variable number. maybe gonna add to strcutures
	double old_plane_y;		// gonna find way to decrease variable number. maybe gonna add to strcutures
	double new_x;			// gonna find way to decrease variable number. maybe gonna add to strcutures
	double new_y;			// gonna find way to decrease variable number. maybe gonna add to strcutures

    if (game->p->p_rot != 0)
    {
		old_dir_x = game->p->dir_x;
		old_plane_x = game->p->plane_x;
		game->p->dir_x = game->p->dir_x * cos(game->p->p_rot * rot_speed) 
			- game->p->dir_y * sin(game->p->p_rot * rot_speed);
		game->p->dir_y = old_dir_x * sin(game->p->p_rot * rot_speed)
			+ game->p->dir_y * cos(game->p->p_rot * rot_speed);
		game->p->plane_x = game->p->plane_x * cos(game->p->p_rot * rot_speed)
			 - game->p->plane_y * sin(game->p->p_rot * rot_speed);
		game->p->plane_y = old_plane_x * sin(game->p->p_rot * rot_speed)
			 + game->p->plane_y * cos(game->p->p_rot * rot_speed);
	}
	move_player_cont(game, move_speed, new_x, new_y);
}

static void	move_player_cont(t_game *game, double move_speed, double new_x, double new_y)
{	
	if (game->p->m_up)
	{
		new_x = game->p->pos_x + game->p->dir_x * move_speed;
		new_y = game->p->pos_y + game->p->dir_y * move_speed;
		game->p->pos_x = new_x;
		game->p->pos_y = new_y;
	}
	if (game->p->m_down)
	{
		new_x = game->p->pos_x - game->p->dir_x * move_speed;
		new_y = game->p->pos_y - game->p->dir_y * move_speed;
		game->p->pos_x = new_x;
		game->p->pos_y = new_y;
	}
	if (game->p->m_left)
	{
		new_x = game->p->pos_x - game->p->plane_x * move_speed;
		new_y = game->p->pos_y - game->p->plane_y * move_speed;
		game->p->pos_x = new_x;
		game->p->pos_y = new_y;
	}
	if (game->p->m_right)
	{
		new_y = game->p->pos_y + game->p->plane_y * move_speed;
		new_x = game->p->pos_x + game->p->plane_x * move_speed;
		game->p->pos_x = new_x;
		game->p->pos_y = new_y;
	}
}



int	main(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	init_game(game);
	mlx_key_hook(game->mlx, &key_handler, game);
	mlx_loop(game->mlx);
}
