/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:37:54 by tkirmizi          #+#    #+#             */
/*   Updated: 2025/01/20 12:55:45 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

void	move_player(t_game *game)
{
	double		move_speed;

	move_speed = PLAYER_MOVE_SPEED;
	move_player_forward_back(game, move_speed);
	move_player_left_right(game, move_speed);
	rotate_player(game);
}

void	move_player_forward_back(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	if (game->p->m_up)
	{
		new_x = game->p->pos_x + (game->p->dir_x * move_speed);
		new_y = game->p->pos_y + (game->p->dir_y * move_speed);
		if (is_valid_position(game, new_x, new_y))
		{
			game->p->pos_x = new_x;
			game->p->pos_y = new_y;
		}
	}
	if (game->p->m_down)
	{
		new_x = game->p->pos_x - (game->p->dir_x * move_speed);
		new_y = game->p->pos_y - (game->p->dir_y * move_speed);
		if (is_valid_position(game, new_x, new_y))
		{
			game->p->pos_x = new_x;
			game->p->pos_y = new_y;
		}
	}
}

void	move_player_left_right(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	if (game->p->m_left)
	{
		new_x = game->p->pos_x - game->p->plane_x * move_speed;
		new_y = game->p->pos_y - game->p->plane_y * move_speed;
		if (is_valid_position(game, new_x, new_y))
		{
			game->p->pos_x = new_x;
			game->p->pos_y = new_y;
		}
	}
	if (game->p->m_right)
	{
		new_x = game->p->pos_x + game->p->plane_x * move_speed;
		new_y = game->p->pos_y + game->p->plane_y * move_speed;
		if (is_valid_position(game, new_x, new_y))
		{
			game->p->pos_x = new_x;
			game->p->pos_y = new_y;
		}
	}
}

int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (map_x < 0 || map_y < 0 || map_y
		>= game->mapdata->map_height || map_x
		>= (int)strlen(game->mapdata->map_layout[map_y]))
		return (0);
	if (game->mapdata->map_layout[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	rotate_player(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->p->p_rot != 0)
	{
		old_dir_x = game->p->dir_x;
		game->p->dir_x = game->p->dir_x * cos(game->p->p_rot)
			- game->p->dir_y * sin(game->p->p_rot);
		game->p->dir_y = old_dir_x * sin(game->p->p_rot)
			+ game->p->dir_y * cos(game->p->p_rot);
		old_plane_x = game->p->plane_x;
		game->p->plane_x = game->p->plane_x * cos(game->p->p_rot)
			- game->p->plane_y * sin(game->p->p_rot);
		game->p->plane_y = old_plane_x * sin(game->p->p_rot)
			+ game->p->plane_y * cos(game->p->p_rot);
	}
}
