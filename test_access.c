#include "cup3d.h"
# include "MLX42/MLX42.h"

int main()
{
    t_mlx_render mlx_data;
    mlx_data.floor_c = 0;
    mlx_data.ceiling_c = 0;

    read_colors("map.cub", &mlx_data);

    printf("Floor Color: %#x\n", mlx_data.floor_c);
    printf("Ceiling Color: %#x\n", mlx_data.ceiling_c);

    return 0;
}
