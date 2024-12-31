/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:25 by vodebunm          #+#    #+#             */
/*   Updated: 2024/12/31 03:24:50 by vodebunm         ###   ########.fr       */
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
			texture_input(line_ptr, mlx_data);
		}
		else if (line_ptr[0] == 'F' || line_ptr[0] == 'C')
		{
			color_input(); //To implement
		}
		else if (line_ptr[0] == '1' || line_ptr[0] == '0')
		{
			map_layout_input(line_ptr, mlx_data->map_data);
		}
		free(line_ptr);
	}
	close(fd);
}
