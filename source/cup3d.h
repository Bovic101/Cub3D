/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cup3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:07:34 by tkirmizi          #+#    #+#             */
/*   Updated: 2025/01/20 17:20:46 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUP3D_H
# define CUP3D_H

# include "MLX42/MLX42.h"
# include "get_next_line.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h> // open() function header
# include <limits.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define DISPLAY_HEIGHT 900
# define DISPLAY_WIDTH 1600
# define BLOCK_SIZE 40
# define VIEW_ANGLE 45
# define PLAYER_MOVE_SPEED 1.5 // Player movement per frame
# define TURNING_SPEED 0.03    // Turning speed
# define MAX_MAP_HEIGHT 100    // Max rows in the map
# define MAX_MAP_WIDTH 100     // Max columns in the map
# define R_MULTI 16777216
# define G_MULTI 65536
# define B_MULTI 256

// Structure for map data
typedef struct s_map_data
{
	int		player_block_x;
	int		player_block_y;
	int		map_width;
	int		map_height;
	int		allocated_height; // track allocated height for dynamic resizing
	char	**map_layout; // Pointer to a 2D array
}					t_map_data;
// Structure for player data
typedef struct s_player
{
	double	pos_x; // Player horizontal coordinate in pixels
	double	pos_y; // Player vertical coordinate in pixels
	double	p_rot; // Player rotation flag
	double	p_speed; // Player speed
	double	dir_x; // Player's facing direction X
	double	dir_y; // Player's facing direction Y
	float	plane_x; // Camera plane X
	float	plane_y; // Camera plane Y
	double	field_view; // Player's field of view in radians
	int		m_up; // Move up flag
	int		m_down; // Move down flag
	int		m_right; // Move right flag
	int		m_left; // Move left flag
}					t_player_data;

// Structure for rendering and game attributes
typedef struct s_mlx
{
	t_player_data	*player; // Player data struct
	t_map_data		*map_data; // Map containing map and player info
	/* Game Rendering */
	mlx_image_t		*game_image; // Image to render the game
	mlx_t			*ptr_img; // MLX window pointer
	mlx_texture_t	*xpm_texture[4]; // Textures for walls
	int				floor_c; // Floor color
	int				ceiling_c; // Ceiling color
}					t_mlx_render;

// Structure for game data
typedef struct s_game
{
	t_player_data	*p; // Player data
	t_mlx_render	*mlx_r; // Rendering data
	t_map_data		*mapdata; // Map data
	mlx_t			*mlx; // MLX window
	mlx_image_t		*screen; // Screen image
	int				ceiling_c;
	int				floor_c;
	struct s_rc		*rc;
	int				window_width;
	int				window_height;
}					t_game;

typedef struct s_rc
{
	double			camera_x; // rays coordinate in cam between -1 and 1
	double			ray_dir_x; // x ray vector 
	double			ray_dir_y; // y ray vector
	int				map_x; // x coordinate in map grid
	int				map_y; // y coordinate in map grid
	double			side_dist_x; // distance to next x grid line
	double			side_dist_y; // distance to next y grid line
	double			delta_dist_x; // fixed distance between x grid lines
	double			delta_dist_y; // fixed distance between y grid lines
	int				step_x; // direction to step in x -1 to 1
	int				step_y; // direction to setep in y -1 to 1
	int				hit; // hit to wall ?
	int				side; // hitted wall side 0x 1y
	double			perp_wall_dist; // for fish eye fix
	int				line_height; // vector y of line
	int				draw_start; // y coordinate start
	int				draw_end; // y coordinate end
	double			wall_x; // exact coordinate where hit
	int				tex_x; // texture x coordinate
	int				tex_y; // texture y coordinate
	int				tex_num; // texture selector
	double			step; // about texture increase
	double			tex_pos; // texture position
	struct s_rgb	*rgb;
}					t_rc;

typedef struct s_rgb
{
	uint8_t			*pixel;
	uint32_t		color;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a; // alpha 0-255
}					t_rgb;

// Function prototypes
double				degree_to_radian(double value);
int					is_surrounded_by_walls(t_map_data *map_data, int i, int j);
void				confirm_map_data(t_map_data *map_data);
void				debug_print_map(t_map_data *map_data);
void				player_pos_init(t_mlx_render *mlx_data);
int					process_cub_line(char *trimmed_line, t_mlx_render *mlx_data,
						int fd);
void				texture_loader(const char *texture_path,
						mlx_texture_t **texture_pos);
int					open_cub_file(const char *map_file);
int					cub_file_loader(const char *map_file,
						t_mlx_render *mlx_data);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
void				allocate_map_layout(t_map_data *map_data);
void				texture_input(const char *line_ptr, t_mlx_render *mlx_data);
void				print_error(const char *string);
void				map_layout_input(const char *line_ptr,
						t_map_data *map_data);
void				check_map_character(t_map_data *map_data, int i,
						int *player_count);

// Movement, keybinding, raycasting, etc.
void				move_player(t_game *game);
void				init_game(t_game *game, const char *map_file);
void				cleanup_game(t_game *game);
void				init_player(t_game *game);
void				key_handler(mlx_key_data_t keydata, void *param);
void				init_window(t_game *game);
void				game_loop(void *param);
void				move_player_forward_back(t_game *game, double move_speed);
void				move_player_left_right(t_game *game, double move_speed);
void				free_split(char **split);
void				parse_color_line(t_mlx_render *mlx_data, const char *line);
void				read_colors(const char *file_path, t_mlx_render *mlx_data);
void				rotate_player(t_game *game);
int					is_valid_position(t_game *game, double x, double y);
void				cleanup_game(t_game *game);
void				key_handler_sec(mlx_key_data_t keydata, t_game *game);
void				ft_draw_ceiling_floor(t_game *game);
void				ft_cast_rays(t_game *game, int x, int y);
void				ft_perform_dda(t_game *game);
void				ft_render_wall(t_game *game, int x, int y);
void				ft_texture_selection(t_rc **rc);
void				ft_cast_ray_fabs(t_rc **rc, t_game *game, int x);
void				ft_cast_ray_fabs_cont(t_game *game, t_rc *temp, int x);
void				ft_render_wall_cont(t_game **game, int x, int y);
void				ft_rgb_modifier(t_rgb *rgb);
void				ft_exit_in_wall(char *str);
void				cleanup_game_wout_exit(t_game *game);
void				ft_render_wall_cont_sec(t_game **game, int *y);
void				ft_map_data_mod(t_game **param);
void				ft_rgb_assigner(t_rgb **param);
void				ft_wall_render_helper(t_game **param);
void				cleanup_game_sec(t_game **param);
void				cleanup_game_wout_exit_sec(t_game **param);
uint32_t			create_rgba(int r, int g, int b, int a);
uint32_t			parse_color(const char *line);
void				ft_resize_handle(int32_t widht, int32_t height,
						void *param);

#endif