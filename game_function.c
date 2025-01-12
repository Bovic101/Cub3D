/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor-linux <victor-linux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:25 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/12 17:00:20 by victor-linu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*Function that load the .cub file*/
void cub_file_loader(const char *cub_filename, t_mlx_render *mlx_data)
{
    printf("status: Attempting to open file: '%s'\n", cub_filename);

    int fd = open(cub_filename, O_RDONLY);
    if (fd == -1)
    {
        perror("status: Open failed");
        print_error("Error: Unable to open .cub file\n");
    }

    char *line_ptr = NULL;
    while ((line_ptr = get_next_line(fd)) != NULL)
    {
        printf("status: Read line: %s\n", line_ptr);
        if (line_ptr[0] == '\n' || line_ptr[0] == '\0') // Skip empty lines
        {
            free(line_ptr);
            continue;
        }
        if (line_ptr[0] == 'N' || line_ptr[0] == 'S' || line_ptr[0] == 'W' || line_ptr[0] == 'E')  // Texture parsing
            texture_input(line_ptr, mlx_data);
        else if (line_ptr[0] == 'F' || line_ptr[0] == 'C')
            parse_color_line(mlx_data, line_ptr);
        else if (line_ptr[0] == '1' || line_ptr[0] == '0')
            map_layout_input(line_ptr, mlx_data->map_data);
        else
        {
            free(line_ptr);
            print_error("Error: Unknown line in .cub file\n");
        }

        free(line_ptr);
    }

    if (close(fd) == -1)
        print_error("Error: Unable to close .cub file\n");
}







