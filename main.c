/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:35:05 by taha              #+#    #+#             */
/*   Updated: 2025/01/03 13:27:47 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cup3d.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);

	init_game(game);
	// init_test_map(game); 		for test before map parsing
	// init_player_for_test(game);	for test before map parsing

	mlx_key_hook(game->mlx, &key_handler, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);

	return (0);
}




void	init_window(t_game *game)
{
	game->mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cup3d", false);
	if (!game->mlx)
		return; // error handling ekle

	game->screen = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game->screen)
	{
		mlx_terminate(game->mlx);
		return; // error handling ekle
	}
}
void	init_player(t_game *game)
{
	t_game *game_change;
	game_change = game;
	game_change->p->pos_x = 0;
	game_change->p->pos_y = 0;
	game_change->p->dir_x = -1;
	game_change->p->dir_y = 0;
	game_change->p->plane_x = 0;
	game_change->p->plane_y = 0.66;
	game_change->p->p_rot = TURNING_SPEED;
	game_change->p->p_speed = PLAYER_MOVE_SPEED;
	game_change->p->m_down = 0; // gs
	game_change->p->m_up = 0; // gs
	game_change->p->m_left = 0; // gs
	game_change->p->m_right = 0; // gs
	game_change->p->field_view = VIEW_ANGLE;
}

void init_game(t_game *game)
{
	game->p = malloc(sizeof(t_player_data));
	game->rc = malloc(sizeof(t_raycasting));
	game->mapdata = malloc(sizeof(t_map_data));
	game->mlx_r = malloc(sizeof(t_mlx_render));
	init_window(game);
	init_player(game);
	game->rc->corrected_dist = 1.0f;
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


void	move_player_forward_back(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

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
}

void	move_player_left_right(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	if (game->p->m_left)
	{
		new_x = game->p->pos_x - game->p->plane_x * move_speed;
		new_y = game->p->pos_y - game->p->plane_y * move_speed;
		game->p->pos_x = new_x;
		game->p->pos_y = new_y;
	}
	if (game->p->m_right)
	{
		new_x = game->p->pos_x + game->p->plane_x * move_speed;
		new_y = game->p->pos_y + game->p->plane_y * move_speed;
		game->p->pos_x = new_x;
		game->p->pos_y = new_y;
	}
}

void	move_player(t_game *game)
{
	double	move_speed;

	move_speed = PLAYER_MOVE_SPEED;
	move_player_forward_back(game, move_speed);
	move_player_left_right(game, move_speed);
}

void game_loop(void *param)
{
	t_game *game = (t_game *)param;
	static int initialized = 0;

	ft_memset(game->screen->pixels, 0,
		game->screen->width * game->screen->height * sizeof(uint32_t));
	move_player(game);
	ft_cast_ray(game);
	if (!initialized)
	{
		if (mlx_image_to_window(game->mlx, game->screen, 0, 0) < 0)
		{
			mlx_close_window(game->mlx);
			return;
		}
		initialized = 1;
	}
}


void ft_cast_ray(t_game *game)
{
	float ray_angle;
	float angle_step;
	int x;

	ray_angle = game->p->field_view - (VIEW_ANGLE / 2.0f);
	angle_step = VIEW_ANGLE / (float)DISPLAY_WIDTH;

	x = 0;
	while (x < DISPLAY_WIDTH)
	{
		game->rc->ray_angle = ft_normalize_angle(ray_angle);
		game->rc->cos_angle = cos(game->rc->ray_angle);
		game->rc->sin_angle = sin(game->rc->ray_angle);
		ft_ray_hit(game); 
		ft_draw_walls(game, x);  
		ray_angle += angle_step;
		x++;
	}
}
void ft_draw_walls(t_game *game, int column)
{
	int wall_top;
	int wall_bottom;
	int y;
	int wall_height;

	wall_height = (BLOCK_SIZE / game->rc->corrected_dist) * (DISPLAY_WIDTH / 2);
	wall_top = (DISPLAY_HEIGHT / 2) - (wall_height / 2);
	wall_bottom = (DISPLAY_HEIGHT / 2) + (wall_height / 2);

	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= DISPLAY_HEIGHT)
		wall_bottom = DISPLAY_HEIGHT - 1;

	y = 0;
	while (y < wall_top)
		((uint32_t *)game->screen->pixels)[y++ * DISPLAY_WIDTH + column] = game->ceiling_c;

	while (y < wall_bottom)
		((uint32_t *)game->screen->pixels)[y++ * DISPLAY_WIDTH + column] = 0xFF0000; // textures gonna add later

	while (y < DISPLAY_HEIGHT)
		((uint32_t *)game->screen->pixels)[y++ * DISPLAY_WIDTH + column] = game->floor_c;
}



float	ft_normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return angle;
}

void	ft_find_intersections(t_game *game, t_calc *calc)
{
	calc->y_intersect = floor(game->p->pos_y / BLOCK_SIZE) * BLOCK_SIZE;
	if (game->rc->sin_angle > 0)
		calc->y_intersect += BLOCK_SIZE;
	calc->x_intersect = game->p->pos_x + (calc->y_intersect - game->p->pos_y)
		/ tan(game->rc->ray_angle);
	calc->y_step = BLOCK_SIZE;
	if (game->rc->sin_angle < 0)
		calc->y_step *= -1;
	calc->x_step = BLOCK_SIZE / tan(game->rc->ray_angle);
	if (game->rc->cos_angle < 0 && calc->x_step > 0)
		calc->x_step *= -1;
	if (game->rc->cos_angle > 0 && calc->x_step < 0)
		calc->x_step *= -1;
}

void	ft_ray_hit(t_game *game)
{
	t_calc	calc;
	float	next_x;
	float	next_y;

	ft_find_intersections(game, &calc);
	next_x = calc.x_intersect;
	next_y = calc.y_intersect;
	while (1)
	{
		if (ft_check_wall_hit(game, next_x, next_y))
		{
			ft_set_hit_values(game, next_x, next_y);
			break ;
		}
		if (next_x < 0 || next_y < 0
			|| next_x >= game->mapdata->map_width * BLOCK_SIZE
			|| next_y >= game->mapdata->map_height * BLOCK_SIZE)
			break ;
		next_x += calc.x_step;
		next_y += calc.y_step;
	}
}

void	ft_set_hit_values(t_game *game, float nx, float ny)
{
	game->rc->hit_x = nx;
	game->rc->hit_y = ny;
	game->rc->hit_vertical = 0;
	game->rc->distance = sqrt(pow(nx - game->p->pos_x, 2)
			+ pow(ny - game->p->pos_y, 2));
}

int	ft_check_wall_hit(t_game *game, float nx, float ny)
{
	int	map_x;
	int	map_y;

	if (nx < 0 || nx >= game->mapdata->map_width * BLOCK_SIZE
		|| ny < 0 || ny >= game->mapdata->map_height * BLOCK_SIZE)
		return (0);
	map_x = (int)(nx / BLOCK_SIZE);
	map_y = (int)(ny / BLOCK_SIZE);
	if (map_y >= game->mapdata->map_height || map_x >= game->mapdata->map_width)
		return (0);
	return (game->mapdata->map_layout[map_y][map_x] == '1');
}


// void	init_test_map(t_game *game) // to test before map parsing
// {
// 	int	i;
// 	int	j;

// 	game->mapdata->map_width = 10;
// 	game->mapdata->map_height = 10;
// 	game->mapdata->map_layout = malloc(sizeof(char *) * game->mapdata->map_height);
// 	i = 0;
// 	while (i < game->mapdata->map_height)
// 	{
// 		game->mapdata->map_layout[i] = malloc(sizeof(char) * game->mapdata->map_width);
// 		j = 0;
// 		while (j < game->mapdata->map_width)
// 		{
// 			if (i == 0 || i == game->mapdata->map_height - 1 || 
// 				j == 0 || j == game->mapdata->map_width - 1)
// 				game->mapdata->map_layout[i][j] = '1';
// 			else
// 				game->mapdata->map_layout[i][j] = '0';
// 			j++;
// 		}
// 		i++;
// 	}
// 	game->mapdata->player_block_y = 1;
// 	game->mapdata->player_block_x = 1;
// }

// void init_player_for_test(t_game *game)
// {
// 	game->p->pos_x = (game->mapdata->player_block_x + 0.5) * BLOCK_SIZE;
// 	game->p->pos_y = (game->mapdata->player_block_y + 0.5) * BLOCK_SIZE;
// 	game->p->dir_x = -1;
// 	game->p->dir_y = 0;  
// 	game->p->plane_x = 0;
// 	game->p->plane_y = 0.66;
// }
