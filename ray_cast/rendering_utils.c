/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:40:30 by tkirmizi          #+#    #+#             */
/*   Updated: 2025/01/20 12:50:10 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

void	ft_wall_render_helper(t_game **param)
{
	t_game	*game;

	game = *param;
	game->rc->tex_y = (int)game->rc->tex_pos % 64;
	game->rc->tex_pos += game->rc->step;
	game->rc->rgb->pixel = &game->mlx_r->xpm_texture[game->rc->tex_num]
		-> pixels[(game->rc->tex_y * 64 + game->rc->tex_x) * 4];
}

void	ft_rgb_assigner(t_rgb **param)
{
	t_rgb	*rgb;

	rgb = *param;
	rgb->r = rgb->pixel[3];
	rgb->g = rgb->pixel[2];
	rgb->b = rgb->pixel[1];
	rgb->a = rgb->pixel[0];
}

void	ft_exit_in_wall(char *str)
{
	print_error(str);
	exit(1);
}
