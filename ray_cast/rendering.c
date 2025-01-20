/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:39:20 by tkirmizi          #+#    #+#             */
/*   Updated: 2025/01/20 12:53:00 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

void	game_loop(void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = (t_game *)param;
	y = -1;
	x = -1;
	if (!game || !game->screen || !game->screen->pixels)
	{
		printf("Invalid game state in game loop\n");
		return ;
	}
	move_player(game);
	ft_draw_ceiling_floor(game);
	y = -1;
	x = -1;
	ft_cast_rays(game, x, y);
}

void	ft_draw_ceiling_floor(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < DISPLAY_HEIGHT)
	{
		x = -1;
		while (++x < DISPLAY_WIDTH)
		{
			if (y < DISPLAY_HEIGHT / 2)
				((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
					+ x] = game->mlx_r->ceiling_c;
			else
				((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
					+ x] = game->mlx_r->floor_c;
		}
	}
}

void	ft_render_wall(t_game *game, int x, int y)
{
	if (!game || !game->screen || !game->screen->pixels)
		ft_exit_in_wall("error: invalid game or screen");
	if (game->rc->side == 0)
		game->rc->perp_wall_dist = (game->rc->side_dist_x
				- game->rc->delta_dist_x);
	else
		game->rc->perp_wall_dist = (game->rc->side_dist_y
				- game->rc->delta_dist_y);
	game->rc->line_height = (int)(DISPLAY_HEIGHT / game->rc->perp_wall_dist);
	game->rc->draw_start = -game->rc->line_height / 2 + DISPLAY_HEIGHT / 2;
	if (game->rc->draw_start < 0)
		game->rc->draw_start = 0;
	game->rc->draw_end = game->rc->line_height / 2 + DISPLAY_HEIGHT / 2;
	if (game->rc->draw_end >= DISPLAY_HEIGHT)
		game->rc->draw_end = DISPLAY_HEIGHT - 1;
	y = game->rc->draw_start;
	game->rc->step = 1.0 * 64 / game->rc->line_height;
	game->rc->tex_pos = (game->rc->draw_start - DISPLAY_HEIGHT / 2
			+ game->rc->line_height / 2) * game->rc->step;
	if (game->rc->side == 0 && game->rc->ray_dir_x > 0)
		game->rc->tex_x = 64 - game->rc->tex_x - 1;
	if (game->rc->side == 1 && game->rc->ray_dir_y < 0)
		game->rc->tex_x = 64 - game->rc->tex_x - 1;
	ft_texture_selection(&game->rc);
	ft_render_wall_cont(&game, x, y);
}

void	ft_render_wall_cont(t_game **game, int x, int y)
{
	t_game	*temp;

	temp = *game;
	ft_render_wall_cont_sec(game, &y);
	while (y <= temp->rc->draw_end)
	{
		ft_wall_render_helper(&temp);
		ft_rgb_assigner(&temp->rc->rgb);
		temp->rc->rgb->color = create_rgba(temp->rc->rgb->r,
				temp->rc->rgb->g, temp->rc->rgb->b, temp->rc->rgb->a);
		if (temp->rc->side == 1)
			create_rgba(temp->rc->rgb->r, temp->rc->rgb->g,
				temp->rc->rgb->b, temp->rc->rgb->a);
		((uint32_t *)temp->screen->pixels)
		[((y++) * DISPLAY_WIDTH) + x] = temp->rc->rgb->color;
	}
}

void	ft_render_wall_cont_sec(t_game **game, int *y)
{
	t_game	*temp;

	temp = *game;
	if (temp->rc->side == 0)
		temp->rc->wall_x = temp->p->pos_y / BLOCK_SIZE
			+ temp->rc->perp_wall_dist * temp->rc->ray_dir_y;
	else
		temp->rc->wall_x = temp->p->pos_x / BLOCK_SIZE
			+ temp->rc->perp_wall_dist * temp->rc->ray_dir_x;
	temp->rc->wall_x -= floor(temp->rc->wall_x);
	temp->rc->tex_x = (int)(temp->rc->wall_x * 64.0);
	*y = temp->rc->draw_start;
}
