/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:35:05 by taha              #+#    #+#             */
/*   Updated: 2025/01/14 19:29:28 by victor-linu      ###   ########.fr       */
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
	if (!init_game(&game, argv[1]))
	{
		printf("Failed to initialize game\n");
		return (1);
	}
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Cub3D", true);
	if (!game->mlx)
	{
		write(2, "Error: Failed to initialize mlx\n", 32);
		exit(1);
	}
	game->screen = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!game->screen || !game->screen->pixels)
	{
		write(2, "Error: Failed to create screen image\n", 37);
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
	game->p = malloc(sizeof(t_player_data));
	game->rc = malloc(sizeof(t_raycasting));
	game->mapdata = malloc(sizeof(t_map_data));
	game->mlx_r = malloc(sizeof(t_mlx_render));
	if (!game->p || !game->rc || !game->mapdata || !game->mlx_r)
	{
		print_error("Error: Memory allocation failed in initialize_game\n");
		return (0);
	}
	// Initialize map data
	game->mapdata->map_layout = NULL;
	game->mapdata->map_width = 0;
	game->mapdata->map_height = 0;
	game->mapdata->allocated_height = 0;
	// Initialize rendering components
	game->mlx_r->map_data = game->mapdata;
	game->mlx_r->player = game->p;
	game->mlx_r->floor_c = 0x383838FF;
	game->mlx_r->ceiling_c = 0x1E1E1EFF;
	cub_file_loader(map_file, game->mlx_r);  // Load the map.cub file and map data
	player_pos_init(game->mlx_r); // Initialize the player's position
	init_window(game);
	if (!game->mlx || !game->screen)
	{
		print_error("Error: Failed to initialize the game window\n");
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
	if (game->rc)
		free(game->rc);
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
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->p->m_up = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
				|| keydata.action == MLX_REPEAT))
		game->p->m_down = 1;
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
			&& keydata.action == MLX_RELEASE)
	{
		game->p->m_up = 0;
		game->p->m_down = 0;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->p->m_left = 1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
				|| keydata.action == MLX_REPEAT))
		game->p->m_right = 1;
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
			&& keydata.action == MLX_RELEASE)
	{
		game->p->m_right = 0;
		game->p->m_left = 0;
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->p->p_rot = TURNING_SPEED;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
				|| keydata.action == MLX_REPEAT))
		game->p->p_rot = -TURNING_SPEED;
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
			&& keydata.action == MLX_RELEASE)
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
		if (is_valid_position(game, new_x, new_y))
		{
			game->p->pos_x = new_x;
			game->p->pos_y = new_y;
		}
	}
	if (game->p->m_down)
	{
		new_x = game->p->pos_x - game->p->dir_x * move_speed;
		new_y = game->p->pos_y - game->p->dir_y * move_speed;
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

	if (x < 0 || y < 0 ||
		x >= game->mapdata->map_width * BLOCK_SIZE ||
		y >= game->mapdata->map_height * BLOCK_SIZE)
		return (0);
	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (game->mapdata->map_layout[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	move_player(t_game *game)
{
	double	move_speed;

	move_speed = PLAYER_MOVE_SPEED;
	move_player_forward_back(game, move_speed);
	move_player_left_right(game, move_speed);
	rotate_player(game); // Dönüş kontrolü ekle
}

void	game_loop(void *param)
{
	t_game	*game;
	int		column;

	game = (t_game *)param;
	column = 0;
	while (column < DISPLAY_WIDTH)
	{
		ft_cast_ray(game, column);
		ft_draw_walls(game, column);
		column++;
	}
	mlx_image_to_window(game->mlx, game->screen, 0, 0); // Render to the window
}

void	ft_init_ray(t_game *game, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)DISPLAY_WIDTH - 1;
	ray->dir_x = game->p->dir_x + game->p->plane_x * camera_x;
	ray->dir_y = game->p->dir_y + game->p->plane_y * camera_x;
	ray->pos_x = game->p->pos_x;
	ray->pos_y = game->p->pos_y;
	ray->dist = 0;
	ray->hit = 0;
	ray->step = 1.0;
}

int	ft_check_wall_hit(t_game *game, double pos_x, double pos_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(pos_x / BLOCK_SIZE);
	map_y = (int)(pos_y / BLOCK_SIZE);
	if (map_x >= 0 && map_x < game->mapdata->map_width && map_y >= 0
		&& map_y < game->mapdata->map_height)
	{
		if (game->mapdata->map_layout[map_y][map_x] == '1')
			return (1);
	}
	return (0);
}

void	ft_cast_single_ray(t_game *game, t_ray *ray)
{
	int	max_dist;

	max_dist = (game->mapdata->map_width + game->mapdata->map_height)
		* BLOCK_SIZE;
	while (!ray->hit && ray->dist < max_dist)
	{
		ray->pos_x += ray->dir_x * ray->step;
		ray->pos_y += ray->dir_y * ray->step;
		ray->dist += ray->step;
		ray->hit = ft_check_wall_hit(game, ray->pos_x, ray->pos_y);
	}
}

void	ft_fix_fisheye(t_game *game, t_ray *ray)
{
	double	angle;
	double	player_angle;
	double	fix_angle;

	angle = atan2(ray->dir_y, ray->dir_x);
	player_angle = atan2(game->p->dir_y, game->p->dir_x);
	fix_angle = angle - player_angle;
	if (fix_angle < 0)
		fix_angle += 2 * M_PI;
	else if (fix_angle > 2 * M_PI)
		fix_angle -= 2 * M_PI;
	ray->dist = ray->dist * cos(fix_angle);
}

void	ft_draw_vertical_line(t_game *game, int column, double dist)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;

	line_height = (int)(DISPLAY_HEIGHT / dist);
	draw_start = -line_height / 2 + DISPLAY_HEIGHT / 2;
	draw_end = line_height / 2 + DISPLAY_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= DISPLAY_HEIGHT)
		draw_end = DISPLAY_HEIGHT - 1;
	y = 0;
	while (y < draw_start) // Draw ceiling
	{
		((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
			+ column] = game->ceiling_c;
		y++;
	}
	while (y < draw_end)
	{
		((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
			+ column] = 0xFF0000FF;
		y++;
	}
	while (y < DISPLAY_HEIGHT) // Draw floor
	{
		((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
			+ column] = game->floor_c;
		y++;
	}
}

double	ft_cast_ray(t_game *game, int x)
{
	double	ray_angle;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
	double	corrected_dist;

	ray_angle = game->p->field_view * ((double)x / DISPLAY_WIDTH - 0.5);
	ray_angle = ft_normalize_angle(ray_angle);
	game->rc->ray_angle = ray_angle;
	delta_dist_x = fabs(1 / cos(ray_angle));
	delta_dist_y = fabs(1 / sin(ray_angle));
	int step_x, step_y;
	double side_dist_x, side_dist_y;
	map_x = (int)(game->p->pos_x / BLOCK_SIZE);
	map_y = (int)(game->p->pos_y / BLOCK_SIZE);
	if (cos(ray_angle) > 0)
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - (game->p->pos_x / BLOCK_SIZE))
			* delta_dist_x;
	}
	else
	{
		step_x = -1;
		side_dist_x = ((game->p->pos_x / BLOCK_SIZE) - map_x) * delta_dist_x;
	}
	if (sin(ray_angle) > 0)
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - (game->p->pos_y / BLOCK_SIZE))
			* delta_dist_y;
	}
	else
	{
		step_y = -1;
		side_dist_y = ((game->p->pos_y / BLOCK_SIZE) - map_y) * delta_dist_y;
	}
	hit = 0;
	side = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (game->mlx_r->map_data->map_layout[map_y][map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		corrected_dist = (side_dist_x - delta_dist_x);
	else
		corrected_dist = (side_dist_y - delta_dist_y);
	game->rc->corrected_dist = corrected_dist;
	return (corrected_dist);
}
/*This function perform the raycast and return the ray distance*/
double	perform_raycast(t_game *game, int x)
{
	double	ray_dist;

	ray_dist = ft_cast_ray(game, x);
	return (ray_dist);
}
float	ft_normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	ft_draw_walls(t_game *game, int column)
{
	if (!game || !game->screen || !game->screen->pixels)
	{
		write(2, "Error: Invalid screen or pixels\n", 32);
		return ;
	}
	int wall_top, wall_bottom, wall_height, y = 0;
	wall_height = (int)(DISPLAY_HEIGHT / game->rc->corrected_dist);
	if (wall_height <= 0)
		return ;
	wall_top = (DISPLAY_HEIGHT / 2) - (wall_height / 2);
	wall_bottom = (DISPLAY_HEIGHT / 2) + (wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= DISPLAY_HEIGHT)
		wall_bottom = DISPLAY_HEIGHT - 1;
	while (y < wall_top)
	{
		((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
			+ column] = game->ceiling_c;
		y++;
	}
	while (y < wall_bottom)
	{
		((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
			+ column] = 0xFF0000FF;
		y++;
	}
	while (y < DISPLAY_HEIGHT)
	{
		((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
			+ column] = game->floor_c;
		y++;
	}
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

// void	ft_ray_hit(t_game *game)
// {
// 	t_calc	calc;
// 	float	next_x;
// 	float	next_y;

// 	ft_find_intersections(game, &calc);
// 	next_x = calc.x_intersect;
// 	next_y = calc.y_intersect;
// 	while (1)
// 	{
// 		if (ft_check_wall_hit(game, next_x, next_y))
// 		{
// 			ft_set_hit_values(game, next_x, next_y);
// 			break ;
// 		}
// 		if (next_x < 0 || next_y < 0
// 			|| next_x >= game->mapdata->map_width * BLOCK_SIZE
// 			|| next_y >= game->mapdata->map_height * BLOCK_SIZE)
// 			break ;
// 		next_x += calc.x_step;
// 		next_y += calc.y_step;
// 	}
// }

// void	ft_set_hit_values(t_game *game, float nx, float ny)
// {
// 	game->rc->hit_x = nx;
// 	game->rc->hit_y = ny;
// 	game->rc->hit_vertical = 0;
// 	game->rc->distance = sqrt(pow(nx - game->p->pos_x, 2)
// 			+ pow(ny - game->p->pos_y, 2));
// }

void	init_test_map(t_game *game) // to test before map parsing
{
	int i;
	int j;

	game->mapdata->map_width = 10;
	game->mapdata->map_height = 10;
	game->mapdata->map_layout = malloc(sizeof(char *)
			* game->mapdata->map_height);
	i = 0;
	while (i < game->mapdata->map_height)
	{
		game->mapdata->map_layout[i] = malloc(sizeof(char)
				* game->mapdata->map_width);
		j = 0;
		while (j < game->mapdata->map_width)
		{
			if (i == 0 || i == game->mapdata->map_height - 1 ||
				j == 0 || j == game->mapdata->map_width - 1)
				game->mapdata->map_layout[i][j] = '1';
			else
				game->mapdata->map_layout[i][j] = '0';
			j++;
		}
		i++;
	}
	game->mapdata->player_block_y = 1;
	game->mapdata->player_block_x = 1;
}

void	init_player_for_test(t_game *game)
{
	game->p->pos_x = (1 + 0.5) * BLOCK_SIZE;
	game->p->pos_y = (1 + 0.5) * BLOCK_SIZE;
	game->p->dir_x = -1;
	game->p->dir_y = 0;
	game->p->plane_x = 0;
	game->p->plane_y = 0.66;
}

void	test_draw(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < DISPLAY_HEIGHT / 2)
	{
		x = 0;
		while (x < DISPLAY_WIDTH)
		{
			((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
				+ x] = game->ceiling_c;
			x++;
		}
		y++;
	}
	while (y < DISPLAY_HEIGHT)
	{
		x = 0;
		while (x < DISPLAY_WIDTH)
		{
			((uint32_t *)game->screen->pixels)[y * DISPLAY_WIDTH
				+ x] = game->floor_c;
			x++;
		}
		y++;
	}
	if (!game->screen || mlx_image_to_window(game->mlx, game->screen, 0, 0) < 0)
	{
		mlx_close_window(game->mlx);
		print_error("Failed to put image to window");
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


