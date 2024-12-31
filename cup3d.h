/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cup3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:07:34 by tkirmizi          #+#    #+#             */
/*   Updated: 2024/12/31 01:33:04 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUP3D_H
# define CUP3D_H

# include "MLX42/MLX42.h"
# include <fcntl.h> //open() function header
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include "get_next_line.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define DISPLAY_HEIGHT 900
# define DISPLAY_WIDTH 1600
# define BLOCK_SIZE 40
# define VIEW_ANGLE 45
# define PLAYER_MOVE_SPEED 3 //Player unit- movement per frame
# define TURNING_SPEED 0.1   //turning speed can be change

//Structure for player data and map
typedef struct s_map_data
{
	int				player_block_x;
	int				player_block_y;
	int				map_width;
	int				map_height;
	char **map_layout; //pointer of 2D array
}					t_map_data;

//Structure of player data
typedef struct s_player
{
	int x_cordinate;   //Player horizontal coordinate in pixel
	int y_cordinate;   //Player vertical coordinate in pixel
	int player_rotate; //Player roration flag
	double direction;  //Player's facing direction
	float field_view;  //Player viewpoint at any time(radian)
	int				move_updown;
	int				move_leftright;
}					t_player_data;
//Structure for raycasting
typedef struct s_raycast
{
	/* data */
	//You can populate struct if you like to use it in your implementation
}					t_raycasting;

//Structure for game img ant attribute
typedef struct s_mlx
{
	mlx_image_t *game_image; //Image to render the game
	mlx_t			*ptr_img;
	t_player_data *player;  //player data struct
	t_map_data *s_map_data; //map containing map and player info.
	t_raycasting *raycast;  //To be implemeted by Taha
	mlx_texture_t	*xpm_texture[4];
	//contains the xpm data info. such as width,byte-pixel
	int				floor_c;
	int				ceiling_c;

}					t_mlx_render;
double				degree_to_radian(double value);
void				player_pos_init(t_mlx_render mlx_data);
void	cub_file_loader(const char *cubfile_name, t_mlx_render *mlx_data);

#endif