/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:35:01 by victor-linu       #+#    #+#             */
/*   Updated: 2025/01/20 12:46:01 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/cup3d.h"

/*Function that handles file opening and 
returns the file descriptor*/
int	open_cub_file(const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		print_error("Error: Unable to open .cub file\n");
		return (-1);
	}
	return (fd);
}

/*Function that processes each line from the cub file*/
int	process_cub_line(char *trimmed_line, t_mlx_render *mlx_data, int fd)
{
	if (!trimmed_line || trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (1);
	}
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line,
			"SO ", 3) == 0 || ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0)
		texture_input(trimmed_line, mlx_data);
	else if (ft_strncmp(trimmed_line, "F ", 2) == 0 || ft_strncmp(trimmed_line,
			"C ", 2) == 0)
		parse_color_line(mlx_data, trimmed_line);
	else if (ft_strchr(trimmed_line, '1') || ft_strchr(trimmed_line, '0'))
		map_layout_input(trimmed_line, mlx_data->map_data);
	else
	{
		free(trimmed_line);
		print_error("Error: Unknown or invalid line in .cub file\n");
		close(fd);
		return (0);
	}
	free(trimmed_line);
	return (1);
}

/*Function that manages the file reading loop and 
calls process_cub_line to process each line*/
int	cub_file_loader(const char *map_file, t_mlx_render *mlx_data)
{
	int		fd;
	char	*line_ptr;
	char	*trimmed_line;

	fd = open_cub_file(map_file);
	if (fd == -1)
		return (0);
	line_ptr = get_next_line(fd);
	while (line_ptr != NULL)
	{
		trimmed_line = ft_strtrim(line_ptr, " \n\t\r");
		free(line_ptr);
		if (!process_cub_line(trimmed_line, mlx_data, fd))
			return (0);
		line_ptr = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		print_error("Error: Unable to close .cub file\n");
		return (0);
	}
	confirm_map_data(mlx_data->map_data);
	debug_print_map(mlx_data->map_data);
	return (1);
}
