/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_function_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:26:17 by victor-linu       #+#    #+#             */
/*   Updated: 2025/01/20 12:46:33 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

void	parse_color_line(t_mlx_render *mlx_data, const char *line)
{
	if (line[0] == 'F')
		mlx_data->floor_c = parse_color(line);
	else if (line[0] == 'C')
		mlx_data->ceiling_c = parse_color(line);
}

void	read_colors(const char *file_path, t_mlx_render *mlx_data)
{
	int		fd;
	char	*line;

	if (!file_path || !mlx_data)
		print_error("Error: Invalid arguments passed to read_colors\n");
	return ;
	printf("status: Opening file for reading colors: '%s'\n", file_path);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		perror("status: Open failed");
	print_error("Error: Unable to open .cub file for reading colors\n");
	return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("status: Read line: %s\n", line);
		if (line[0] == 'F' || line[0] == 'C')
			parse_color_line(mlx_data, line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
		print_error("Error: Unable to close .cub file after reading colors\n");
}
