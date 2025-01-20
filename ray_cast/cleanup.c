/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:35:57 by tkirmizi          #+#    #+#             */
/*   Updated: 2025/01/20 12:46:45 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

void	cleanup_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->mapdata)
	{
		while (i < game->mapdata->map_height)
		{
			free(game->mapdata->map_layout[i]);
			i++;
		}
		free(game->mapdata->map_layout);
		free(game->mapdata);
	}
	i = 0;
	if (game->mlx_r)
	{
		while (i < 4)
		{
			if (game->mlx_r->xpm_texture[i])
				mlx_delete_texture(game->mlx_r->xpm_texture[i]);
			i++;
		}
		free(game->mlx_r);
	}
	cleanup_game_sec(&game);
}

void	cleanup_game_sec(t_game **param)
{
	t_game *game;
	game = *param;

	if (game->p)
		free(game->p);
	if (game->rc)
	{
		if (game->rc->rgb)
			free(game->rc->rgb);
		free(game->rc);
	}
	if (game->screen)
		mlx_delete_image(game->mlx, game->screen);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(1);
}

void	cleanup_game_wout_exit(t_game *game)
{
	int	i;

	i = 0;
	if (game->mapdata)
	{
		while (i < game->mapdata->map_height)
		{
			free(game->mapdata->map_layout[i]);
			i++;
		}
		free(game->mapdata->map_layout);
		free(game->mapdata);
	}
	i = 0;
	if (game->mlx_r)
	{
		while (i < 4)
		{
			if (game->mlx_r->xpm_texture[i])
				mlx_delete_texture(game->mlx_r->xpm_texture[i]);
			i++;
		}
		free(game->mlx_r);
	}
	cleanup_game_wout_exit_sec(&game);
}

void	cleanup_game_wout_exit_sec(t_game **param)
{
	t_game *game;
	game = *param;

	if (game->p)
		free(game->p);
	if (game->rc)
	{
		if (game->rc->rgb)
			free(game->rc->rgb);
		free(game->rc);
	}
	if (game->screen)
		mlx_delete_image(game->mlx, game->screen);
	if (game->mlx)
		mlx_terminate(game->mlx);
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