/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:25 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/08 01:39:44 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function that load the .cub file*/
void	cub_file_loader(const char *cubfile_name, t_mlx_render *mlx_data)
{
	int fd;

	fd = open(cubfile_name, O_RDONLY);
	if (fd == -1)
	{
		perror("File unable to open");
		return ;
	}
	char *line_ptr = NULL;
	while ((line_ptr = get_next_line(fd)) != NULL)
	{
		if (line_ptr[0] == 'N' || line_ptr[0] == 'S' || line_ptr[0] == 'W'
			|| line_ptr[0] == 'E')
		{
			texture_input(line_ptr, mlx_data);//parse and load all texture
		}
		else if (line_ptr[0] == 'F' || line_ptr[0] == 'C')
		{
			 //parse color
		}
		else if (line_ptr[0] == '1' || line_ptr[0] == '0')
		{
			map_layout_input(line_ptr, mlx_data->map_data);//parse map layout
		}
		free(line_ptr);
	}
	close(fd);
}
