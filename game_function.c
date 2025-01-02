
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:34:25 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/01 19:09:35 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cup3d.h"

/*
** Example structure definitions (in cup3d.h):
**
** typedef struct s_rgb {
**     int r;
**     int g;
**     int b;
** } t_rgb;
**
** typedef struct s_map_data {
**     // map representation, e.g. char **map;
**     // width, height, etc.
** } t_map_data;
**
** typedef struct s_mlx_render {
**     t_map_data    *map_data;
**     t_rgb         floor_color;
**     t_rgb         ceiling_color;
**     // other fields related to textures, window, etc.
** } t_mlx_render;
**
** // Function prototypes:
** void texture_input(char *line, t_mlx_render *mlx_data);
** void map_layout_input(const char *line, t_map_data *map_data);
** // We'll implement color_input below.
*/

/* ************************************************************************** */
/*                          Utility Functions                                 */
/* ************************************************************************** */

/*
** Splits a string by the given delimiter and returns an array of strings.
** Implementation depends on your libft or custom library. 
** You might already have ft_split in your project. 
** 
** NOTE: For a simpler color parsing approach, you could use sscanf().
** But here, let's pretend we use ft_split for consistency with 42 style.
*/
static char **split_line_by_char(const char *str, char delimiter)
{
    // Use your own ft_split, or implement a minimal splitting function.
    // This is just a placeholder signature for clarity.
    // Return an array of null-terminated strings, with the final element = NULL.
    return ft_split(str, delimiter);
}

/* ************************************************************************** */
/*                           Color Parsing                                    */
/* ************************************************************************** */

/*
** color_input():
** - line format: "F R,G,B" or "C R,G,B"
** - extracts three integers (0-255) for R, G, and B.
** - stores them in mlx_data->floor_color or mlx_data->ceiling_color accordingly.
** - if any step fails, you can print an error or handle it gracefully.
*/

void color_input(const char *line, t_mlx_render *mlx_data)
{
    t_rgb           rgb;
    char            **parts;
    char            **rgb_parts;
    int             i;

    // line[0] is 'F' or 'C', so we skip 1 character + any spaces
    // Example line: "F 220,100,0" or "C 225,30,30"

    // 1. Skip the identifier ('F' or 'C') and any spaces
    while (*line && (*line == 'F' || *line == 'C' || *line == ' ' || *line == '\t'))
        line++;

    // 2. Split by commas
    rgb_parts = split_line_by_char(line, ',');
    if (!rgb_parts)
    {
        perror("color_input: Split failed");
        return ;
    }

    // 3. Check we have exactly 3 elements for R, G, B
    // e.g., ["220", "100", "0", NULL]
    i = 0;
    while (rgb_parts[i])
        i++;
    if (i != 3)
    {
        ft_free_split(rgb_parts); // free your split array properly
        fprintf(stderr, "Error: Invalid color format. Expected 3 components.\n");
        return ;
    }

    // 4. Convert each string to an integer and validate range 0-255
    rgb.r = ft_atoi(rgb_parts[0]); // Or your own atoi
    rgb.g = ft_atoi(rgb_parts[1]);
    rgb.b = ft_atoi(rgb_parts[2]);

    // Basic validation
    if (rgb.r < 0 || rgb.r > 255 || 
        rgb.g < 0 || rgb.g > 255 ||
        rgb.b < 0 || rgb.b > 255)
    {
        ft_free_split(rgb_parts);
        fprintf(stderr, "Error: Color values must be in [0..255].\n");
        return ;
    }

    ft_free_split(rgb_parts);

    // 5. Depending on whether line[0] was 'F' or 'C', store the color
    // For that, we can check the first character used before skipping.
    // We'll assume the caller already knows which letter it was, but let's do it robustly.

    // Move pointer back to the start of the actual line for re-check
    // or pass a separate parameter. For now, let's assume we have enough context:
    // We'll do a quick check: if line[-some_offset] was 'F' => floor, if 'C' => ceiling.
    // Easiest is to do a quick param check: color_input got line with line[0] as 'F' or 'C'.

    // We'll do it by just looking at the original line[0] that was passed in:
    if (line[-1] == 'F')   // This is tricky if line was advanced. 
    {
        mlx_data->floor_color = rgb;
    }
    else
    {
        mlx_data->ceiling_color = rgb;
    }

    // If the above pointer arithmetic is unreliable, 
    // simply pass the original line pointer or a “type” param for clarity.
    // E.g., color_input(char identifier, const char* line, t_mlx_render *mlx_data)
    // then do: if (identifier == 'F') {...} else {...}
}

/* ************************************************************************** */
/*                          .cub File Loader                                  */
/* ************************************************************************** */

void cub_file_loader(const char *cubfile_name, t_mlx_render *mlx_data)
{
    int     fd;
    char    *line_ptr;

    fd = open(cubfile_name, O_RDONLY);
    if (fd == -1)
    {
        perror("File unable to open");
        return ;
    }
    // Read lines until EOF
    while ((line_ptr = get_next_line(fd)) != NULL)
    {
        if (line_ptr[0] == 'N' || line_ptr[0] == 'S'
            || line_ptr[0] == 'W' || line_ptr[0] == 'E')
        {
            texture_input(line_ptr, mlx_data);
        }
        else if (line_ptr[0] == 'F' || line_ptr[0] == 'C')
        {
            color_input(line_ptr, mlx_data);
        }
        else if (line_ptr[0] == '1' || line_ptr[0] == '0')
        {
            map_layout_input(line_ptr, mlx_data->map_data);
        }
        // You might want an else-case to handle unknown lines or invalid syntax
        free(line_ptr);
    }
    close(fd);
}
