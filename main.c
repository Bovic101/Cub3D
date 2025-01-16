/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:35:05 by taha              #+#    #+#             */
/*   Updated: 2025/01/16 19:00:25 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cup3d.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (!init_game(&game, argv[1]))
	{
		printf("Game initialization failed\n");
		cleanup_game(&game);
		return (1);
	}
	mlx_key_hook(game.mlx, &key_handler, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	if (mlx_image_to_window(game.mlx, game.screen, 0, 0) < 0)
	{
		printf("Failed to put image to window\n");
		cleanup_game(&game);
		return (1);
	}
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Cub3D", true);
	if (!game->mlx)
	{
		printf("MLX initialization failed\n");
		exit(1);
	}
	game->screen = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game->screen || !game->screen->pixels)
	{
		printf("Screen creation failed\n");
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

void	rotate_player(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->p->p_rot != 0)
	{
		old_dir_x = game->p->dir_x;
		game->p->dir_x = game->p->dir_x * cos(game->p->p_rot) -
			game->p->dir_y * sin(game->p->p_rot);
		game->p->dir_y = old_dir_x * sin(game->p->p_rot) +
			game->p->dir_y * cos(game->p->p_rot);
		old_plane_x = game->p->plane_x;
		game->p->plane_x = game->p->plane_x * cos(game->p->p_rot) -
			game->p->plane_y * sin(game->p->p_rot);
		game->p->plane_y = old_plane_x * sin(game->p->p_rot) +
			game->p->plane_y * cos(game->p->p_rot);
	}
}

int	init_game(t_game *game, const char *map_file)
{
	memset(game, 0, sizeof(t_game));
	game->p = malloc(sizeof(t_player_data));
	game->mapdata = malloc(sizeof(t_map_data));
	game->mlx_r = malloc(sizeof(t_mlx_render));
	game->rc = malloc(sizeof(t_rc));
	if (!game->p || !game->mapdata || !game->mlx_r)
	{
		printf("Memory allocation failed\n");
		return (0);
	}
	game->mapdata->map_layout = NULL;
	game->mapdata->map_width = 0;
	game->mapdata->map_height = 0;
	game->mapdata->allocated_height = 0;
	game->mlx_r->map_data = game->mapdata;
	game->mlx_r->player = game->p;
	game->mlx_r->floor_c = 0x383838FF;
	game->mlx_r->ceiling_c = 0x1E1E1EFF;
	cub_file_loader(map_file, game->mlx_r);
	player_pos_init(game->mlx_r);
	init_window(game);
	if (!game->mlx || !game->screen)
	{
		printf("Window initialization failed\n");
		return (0);
	}
	if (mlx_image_to_window(game->mlx, game->screen, 0, 0) < 0)
	{
		printf("Failed to put image to window\n");
		return (0);
	}
	return (1);
}
/*Function to free up the game buf*/
void	cleanup_game(t_game *game)
{
	int	i;

	if (game->mapdata)
	{
		i = 0;
		while (i < game->mapdata->map_height)
		{
			free(game->mapdata->map_layout[i]);
			i++;
		}
		free(game->mapdata->map_layout);
		free(game->mapdata);
	}
	if (game->mlx_r)
	{
		i = 0;
		while (i < 4)
		{
			if (game->mlx_r->xpm_texture[i])
				mlx_delete_texture(game->mlx_r->xpm_texture[i]);
			i++;
		}
		free(game->mlx_r);
	}
	if (game->p)
		free(game->p);
	if (game->screen)
		mlx_delete_image(game->mlx, game->screen);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
			game->p->m_up = 1;
		if (keydata.key == MLX_KEY_S)
			game->p->m_down = 1;
		if (keydata.key == MLX_KEY_A)
			game->p->m_left = 1;
		if (keydata.key == MLX_KEY_D)
			game->p->m_right = 1;
		if (keydata.key == MLX_KEY_LEFT)
			game->p->p_rot = -TURNING_SPEED;
		if (keydata.key == MLX_KEY_RIGHT)
			game->p->p_rot = TURNING_SPEED;
	}
	if (keydata.action == MLX_RELEASE)
		key_handler_sec(keydata, game);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
}

void	key_handler_sec(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W)
		game->p->m_up = 0;
	if (keydata.key == MLX_KEY_S)
		game->p->m_down = 0;
	if (keydata.key == MLX_KEY_A)
		game->p->m_left = 0;
	if (keydata.key == MLX_KEY_D)
		game->p->m_right = 0;
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		game->p->p_rot = 0;
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
	if (map_x < 0 || map_y < 0 ||
		map_y >= game->mapdata->map_height ||
		map_x >= (int)strlen(game->mapdata->map_layout[map_y]))
		return (0);
	if (game->mapdata->map_layout[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	move_player(t_game *game)
{
	static int	debug_counter;
	double		move_speed;

	debug_counter = 0;
	move_speed = PLAYER_MOVE_SPEED;
	move_player_forward_back(game, move_speed);
	move_player_left_right(game, move_speed);
	rotate_player(game);
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
		game->rc->camera_x = 2 * x / (double)DISPLAY_WIDTH - 1;
		game->rc->ray_dir_x = game->p->dir_x + game->p->plane_x
			* game->rc->camera_x;
		game->rc->ray_dir_y = game->p->dir_y + game->p->plane_y
			* game->rc->camera_x;
		game->rc->map_x = (int)(game->p->pos_x / BLOCK_SIZE);
		game->rc->map_y = (int)(game->p->pos_y / BLOCK_SIZE);
		game->rc->delta_dist_x = (game->rc->ray_dir_x == 0) ? 1e30 : fabs(1
				/ game->rc->ray_dir_x);
		game->rc->delta_dist_y = (game->rc->ray_dir_y == 0) ? 1e30 : fabs(1
				/ game->rc->ray_dir_y);
		if (game->rc->ray_dir_x < 0)
		{
			game->rc->step_x = -1;
			game->rc->side_dist_x = (game->p->pos_x / BLOCK_SIZE
					- game->rc->map_x) * game->rc->delta_dist_x;
		}
		else
		{
			game->rc->step_x = 1;
			game->rc->side_dist_x = (game->rc->map_x + 1.0 - game->p->pos_x
					/ BLOCK_SIZE) * game->rc->delta_dist_x;
		}
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
			&& game->rc->map_y < game->mapdata->map_height &&
			game->rc->map_x < (int)strlen(game->mapdata->map_layout[game->rc->map_y])
				&&
			game->mapdata->map_layout[game->rc->map_y][game->rc->map_x] == '1')
			game->rc->hit = 1;
	}
}


void	ft_render_wall(t_game *game, int x, int y)
{
	if (!game || !game->screen || !game->screen->pixels)
	{
		print_error("Error: Invalid game or screen buffer\n");
		return ;
	}
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
		if (x == DISPLAY_WIDTH / 2)
		{
			printf("ray hit p = %.3f\n",  game->rc->wall_x);
			printf("texture hit p = %d\n", game->rc->tex_x);
		}
	y = game->rc->draw_start; // gonna check later
	// HERE WILL BE IMPLEMENTATION OF TEXTURES
		if (game->rc->side == 0)
		game->rc->wall_x = game->p->pos_y / BLOCK_SIZE + game->rc->perp_wall_dist * game->rc->ray_dir_y;
	else
	game->rc->wall_x = game->p->pos_x / BLOCK_SIZE + game->rc->perp_wall_dist * game->rc->ray_dir_x;
	game->rc->wall_x -= floor(game->rc->wall_x);
	game->rc->tex_x = (int)(game->rc->wall_x * 64.0);
	y = game->rc->draw_start;
	while (y <= game->rc->draw_end)
	{
		if (y < 0 || y >= DISPLAY_HEIGHT)
		{
			print_error("Error: y out of bounds\n");
			break;
		}
		game->rc->tex_y = ((y - game->rc->draw_start) * 64) / game->rc->line_height;
		game->rc->color = 0xFF0000FF;
		if (game->rc->side == 1)
			game->rc->color = 0x800000FF;
		((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH + x] = game->rc->color;
		y++;
	}
}
uint32_t	create_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

uint32_t	parse_color(const char *line)
{
	char	**split;

	int r, g, b;
	while (*line == 'F' || *line == 'C' || *line == ' ')
		line++;
	split = ft_split(line, ',');
	if (!split)
		print_error("Error: Memory allocation failed in parse_color\n");
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		print_error("Error: Invalid RGB format in parse_color\n");
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_error("Error: RGB values out of range in parse_color\n");
	return (create_rgba(r, g, b, 255));
}
