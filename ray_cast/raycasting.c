/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:38:42 by tkirmizi          #+#    #+#             */
/*   Updated: 2025/01/20 12:54:43 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

void	ft_cast_rays(t_game *game, int x, int y)
{
	if (!game || !game->rc || !game->p)
	{
		write(2, "Error: Invalid game structure\n", 30);
		return ;
	}
	x = -1;
	while (++x < DISPLAY_WIDTH)
	{
		ft_cast_ray_fabs(&(game->rc), game, x);
		if (game->rc->ray_dir_y < 0)
		{
			game->rc->step_y = -1;
			game->rc->side_dist_y = (game->p->pos_y / BLOCK_SIZE
					- game->rc->map_y) * game->rc->delta_dist_y;
		}
		else
		{
			game->rc->step_y = 1;
			game->rc->side_dist_y = (game->rc->map_y + 1.0 - game->p->pos_y
					/ BLOCK_SIZE) * game->rc->delta_dist_y;
		}
		ft_perform_dda(game);
		ft_render_wall(game, x, y);
	}
}

void	ft_cast_ray_fabs(t_rc **rc, t_game *game, int x)
{
	t_rc	*temp;

	temp = *rc;
	temp->camera_x = 2 * x / (double)DISPLAY_WIDTH - 1;
	temp->ray_dir_x = game->p->dir_x + game->p->plane_x * temp->camera_x;
	temp->ray_dir_y = game->p->dir_y + game->p->plane_y * temp->camera_x;
	temp->map_x = (int)(game->p->pos_x / BLOCK_SIZE);
	temp->map_y = (int)(game->p->pos_y / BLOCK_SIZE);
	if (temp->ray_dir_x == 0)
		temp->delta_dist_x = 1e30;
	else
		temp->delta_dist_x = fabs(1 / temp->ray_dir_x);
	if (temp->ray_dir_y == 0)
		temp->delta_dist_y = 1e30;
	else
		temp->delta_dist_y = fabs(1 / temp->ray_dir_y);
	ft_cast_ray_fabs_cont(game, temp, x);
}

void	ft_cast_ray_fabs_cont(t_game *game, t_rc *temp, int x)
{
	(void)x;
	if (temp->ray_dir_x < 0)
	{
		temp->step_x = -1;
		temp->side_dist_x = (game->p->pos_x / BLOCK_SIZE - temp->map_x)
			* temp->delta_dist_x;
	}
	else
	{
		temp->step_x = 1;
		temp->side_dist_x = (temp->map_x + 1.0 - game->p->pos_x / BLOCK_SIZE)
			* temp->delta_dist_x;
	}
}

void	ft_perform_dda(t_game *game)
{
	game->rc->hit = 0;
	while (game->rc->hit == 0)
	{
		if (game->rc->side_dist_x < game->rc->side_dist_y)
		{
			game->rc->side_dist_x += game->rc->delta_dist_x;
			game->rc->map_x += game->rc->step_x;
			game->rc->side = 0;
		}
		else
		{
			game->rc->side_dist_y += game->rc->delta_dist_y;
			game->rc->map_y += game->rc->step_y;
			game->rc->side = 1;
		}
		if (game->rc->map_x >= 0 && game->rc->map_y >= 0
			&& game->rc->map_y < game->mapdata->map_height && game->rc->map_x
			< (int)strlen(game->mapdata->map_layout[game->rc->map_y])
			&& game->mapdata->map_layout[game->rc->map_y]
			[game->rc->map_x] == '1')
			game->rc->hit = 1;
	}
}

void	ft_texture_selection(t_rc **rc)
{
	t_rc	*temp;

	temp = *rc;
	if (temp->side == 0)
	{
		if (temp->ray_dir_x > 0)
			temp->tex_num = 3;
		else
			temp->tex_num = 2;
	}
	else
	{
		if (temp->ray_dir_y > 0)
			temp->tex_num = 1;
		else
			temp->tex_num = 0;
	}
}
