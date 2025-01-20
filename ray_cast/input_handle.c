/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:36:25 by tkirmizi          #+#    #+#             */
/*   Updated: 2025/01/20 12:56:39 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

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

void	ft_resize_handle(int32_t widht, int32_t height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->screen)
		mlx_delete_image(game->mlx, game->screen);
	game->screen = mlx_new_image(game->mlx, widht, height);
	if (!game->screen || !game->screen->pixels)
	{
		printf("error: screen creation fail\n");
		mlx_close_window(game->mlx);
		return ;
	}
	game->window_height = height;
	game->window_width = widht;
	ft_draw_ceiling_floor(game);
	ft_cast_rays(game, 0, 0);
}

uint32_t	parse_color(const char *line)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	while (*line == 'F' || *line == 'C' || *line == ' ')
		line++;
	split = ft_split(line, ',');
	if (!split)
		print_error("error: memory allocation failed in parse_color\n");
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		print_error("error: invalid RGB format in parse_color\n");
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_error("error: RGB values out of range in parse_color\n");
	return (create_rgba(r, g, b, 255));
}

uint32_t	create_rgba(int r, int g, int b, int a)
{
	return ((r * R_MULTI) + (g * G_MULTI) + (b * B_MULTI) + a);
}
