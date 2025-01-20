/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:35:05 by taha              #+#    #+#             */
/*   Updated: 2025/01/20 12:57:33 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "source/cup3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	game.window_height = DISPLAY_HEIGHT;
	game.window_width = DISPLAY_WIDTH;
	init_game(&game, argv[1]);
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_resize_hook(game.mlx, &ft_resize_handle, &game);
	if (mlx_image_to_window(game.mlx, game.screen, 0, 0) < 0)
		cleanup_game(&game);
	mlx_loop(game.mlx);
	cleanup_game_wout_exit(&game);
	return (0);
}

void	init_window(t_game *game)
{
	if (game->window_width <= 0 || game->window_height <= 0)
	{
		exit(1);
	}
	game->mlx = mlx_init(game->window_width, game->window_height, "Cub3D",
			true);
	if (!game->mlx)
	{
		exit(1);
	}
	game->screen = mlx_new_image(game->mlx, game->window_width,
			game->window_height);
	if (!game->screen || !game->screen->pixels)
	{
		mlx_terminate(game->mlx);
		exit(1);
	}
}

void	init_player(t_game *game)
{
	t_game	*game_change;

	game_change = game;
	game_change->p->pos_x = 0;
	game_change->p->pos_y = 0;
	game_change->p->dir_x = -1;
	game_change->p->dir_y = 0;
	game_change->p->plane_x = 0;
	game_change->p->plane_y = 0.66;
	game_change->p->p_rot = TURNING_SPEED;
	game_change->p->p_speed = PLAYER_MOVE_SPEED;
	game_change->p->m_down = 0;
	game_change->p->m_up = 0;
	game_change->p->m_left = 0;
	game_change->p->m_right = 0;
	game_change->p->field_view = VIEW_ANGLE;
}

void	init_game(t_game *game, const char *map_file)
{
	ft_memset(game, 0, sizeof(t_game));
	game->window_width = DISPLAY_WIDTH;
	game->window_height = DISPLAY_HEIGHT;
	game->p = malloc(sizeof(t_player_data));
	game->mapdata = malloc(sizeof(t_map_data));
	game->mlx_r = malloc(sizeof(t_mlx_render));
	game->rc = malloc(sizeof(t_rc));
	game->rc->rgb = malloc(sizeof(t_rgb));
	ft_map_data_mod(&game);
	if (!game->p || !game->mapdata || !game->mlx_r || !game->rc
		|| !game->rc->rgb)
		cleanup_game(game);
	if (cub_file_loader(map_file, game->mlx_r) == 0)
		cleanup_game(game);
	player_pos_init(game->mlx_r);
	init_window(game);
	if (!game->mlx || !game->screen)
		cleanup_game(game);
	if (mlx_image_to_window(game->mlx, game->screen, 0, 0) < 0)
		cleanup_game(game);
}

void	ft_map_data_mod(t_game **param)
{
	t_game	*game;

	game = *param;
	game->mapdata->map_layout = NULL;
	game->mapdata->map_width = 0;
	game->mapdata->map_height = 0;
	game->mapdata->allocated_height = 0;
	game->mlx_r->map_data = game->mapdata;
	game->mlx_r->player = game->p;
	game->mlx_r->floor_c = 0x383838FF;
	game->mlx_r->ceiling_c = 0x1E1E1EFF;
}
