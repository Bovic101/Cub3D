/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:25 by vodebunm          #+#    #+#             */
/*   Updated: 2024/12/30 10:38:26 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function that load the .cub file*/
void cub_file_loader(const char *cubfile_name, t_mlx_render *mlx_data)
{
	int fd;
	char  *character_counter;
	
	fd = open(cubfile_name,O_RDONLY);
	if (fd == -1)
	{
		perror("File unable to open");
		return;
	}
	//Implementation in progress
}