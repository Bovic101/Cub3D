/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:35:05 by taha              #+#    #+#             */
/*   Updated: 2024/12/29 09:18:13 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	// Pencereyi başlat
	mlx = mlx_init(800, 600, "so_long", true);
	if (!mlx)
		return (fprintf(stderr, "MLX başlatılamadı!\n"), 1);
	// PNG görselini yükle
	texture = mlx_load_png("player.png");
	if (!texture)
	{
		fprintf(stderr, "Görsel yüklenemedi!\n");
		mlx_terminate(mlx);
		return (1);
	}
	// Texture'ı pencereye doğrudan yerleştirmek için image'e dönüştür
	img = mlx_new_image(mlx, texture->width, texture->height);
	if (!img)
	{
		fprintf(stderr, "Image oluşturulamadı!\n");
		mlx_delete_texture(texture);
		mlx_terminate(mlx);
		return (1);
	}
	// Texture'ı image'e kopyala
	mlx_texture_to_image(mlx, texture);
	// Görseli pencereye yerleştir
	mlx_image_to_window(mlx, img, 200, 200);
	// Texture'ı serbest bırak
	mlx_delete_texture(texture);
	// Pencereyi başlat
	mlx_loop(mlx);
	// Kaynakları temizle
	mlx_terminate(mlx);
	return (0);
}
