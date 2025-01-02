/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cup3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:07:34 by tkirmizi          #+#    #+#             */
/*   Updated: 2025/01/02 12:59:56 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUP3D_H
# define CUP3D_H

# include "MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h> //open() function header
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define DISPLAY_HEIGHT 900
# define DISPLAY_WIDTH 1600
# define BLOCK_SIZE 40
# define VIEW_ANGLE 45
# define PLAYER_MOVE_SPEED 3 //Player unit- movement per frame
# define TURNING_SPEED 0.1   //turning speed can be change
# define MAX_MAP_HEIGHT 50   // max num. of rows in the map
# define MAX_MAP_WIDTH 50    // min num. of rows in the map

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
	int pos_x;   //Player horizontal coordinate in pixel
	int pos_y;   //Player vertical coordinate in pixel
	double p_rot; //Player roration flag
	double	p_speed;
	double dir_x;  //Player's facing direction
	double dir_y;  //Player's facing direction
	float plane_x;
	float plane_y;
	float field_view;  //Player viewpoint at any time(radian)
	int				m_up;
	int				m_down;
	int				m_right;
	int				m_left;
}					t_player_data;
//Structure for raycasting
typedef struct s_raycast
{
	float ray_angle;
	float distance;
	float hit_x;
	float hit_y;
	int hit_vertical;
	float p_height;
	float p_pos;
	float cos_angle;
	float sin_angle;
	float corrected_dist;
}					t_raycasting;

//Structure for game img ant attribute
typedef struct s_mlx
{
	/*Map Data*/
	t_player_data *player; //player data struct
	t_map_data *map_data;  //map containing map and player info.
	/*Game Randering*/
	mlx_image_t *game_image; //Image to render the game
	mlx_t			*ptr_img;
	mlx_texture_t	*xpm_texture[4];
	int				floor_c;
	int				ceiling_c;
	/*Raycasting*/
	t_raycasting *raycast;  //To be implemeted by Taha
}					t_mlx_render;

typedef struct s_game
{
	t_player_data *p;
	t_mlx_render *mlx_r;
	t_raycasting *rc;
	t_map_data *mapdata;
	mlx_t *mlx;
	mlx_image_t *screen;
	
}	t_game;


typedef struct s_calc
{
	float	x_intersect;
	float	y_intersect;
	float	x_step; // fixed
	float	y_step; // fixed
}	t_calc;



double				degree_to_radian(double value);
void				player_pos_init(t_mlx_render mlx_data);
void	cub_file_loader(const char *cubfile_name,
						t_mlx_render *mlx_data);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
void				texture_input(const char *line_ptr, t_mlx_render *mlx_data);
void				print_error(const char *string);
void				map_layout_input(const char *line_ptr,
						t_map_data *map_data);

// movement, keybinding, ray casting etc...
void move_player(t_game *game);
void	init_game(t_game *game);
void	init_player(t_game *game);
void key_handler(mlx_key_data_t keydata, void *param);
void	move_player_cont(t_game *game, double move_speed, double new_x, double new_y);
void	init_window(t_game *game);
void	game_loop(void *param);
void	ft_cast_ray(t_game *game);
void	ft_find_intersections(t_game *game, t_calc *calc);
int	ft_check_wall_hit(t_game *game, float nx, float ny);
void	ft_set_hit_values(t_game *game, float nx, float ny);
float	ft_normalize_angle(float angle);
void	ft_ray_hit(t_game *game);



#endif