/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:35:05 by taha              #+#    #+#             */
/*   Updated: 2025/01/01 19:22:47 by taha             ###   ########.fr       */
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

void key_handler(mlx_key_data_t keydata, void *param)
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


void move_player(t_game *game)
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

void	move_player_cont(t_game *game, double move_speed, double new_x, double new_y)
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

void	game_loop(void *param)
{
	t_game *game;

	game = param;
	move_player(game);
	ft_cast_ray(game);
}

void	ft_cast_ray(t_game *game)
{
	float	ray_angle;
	float	angle_step;
	int	x;

	ray_angle = game->p->field_view -(VIEW_ANGLE / 2.0f);
	angle_step = VIEW_ANGLE / (float)DISPLAY_WIDTH;
	x = -1;
	while (++x < DISPLAY_WIDTH)
	{
		game->rc->ray_angle = normalize_angle(ray_angle); // gonna add to fix angle
		game->rc->cos_angle = cos(game->rc->ray_angle);
		game->rc->sin_angle = sin(game->rc->ray_angle);
		// ft_ray_hit(game) 		gonna add
		// cal_wall_height (game)	gonna add
		ray_angle += angle_step;
	}
}

float normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return angle;
}

void	ft_ray_hit(t_game *game)
{
	t_calc	calc;
	float	next_x;
	float	next_y;

	// find_intersections() gonna add to find intersections
	next_x = calc.x_intersect;
	next_y = calc.y_intersect;
	while (1)
	{
		if (check_wall_hit(game, next_x, next_y))
		{
			game->rc->hit_x = next_x;
			game->rc->hit_y = next_y;
			game->rc->hit_vertical = 0;
			game->rc->distance = sqrt(pow(next_x - game->p->pos_x, 2)
					+ pow(next_y - game->p->pos_y, 2));
			break ;
		}
		next_x += calc.x_step;
		next_y += calc.y_step;
	}
}

// void	cal_wall_height(t_game *game)


int	main(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	init_game(game);
	mlx_key_hook(game->mlx, &key_handler, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
}
