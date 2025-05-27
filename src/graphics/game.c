#include "../../include/cub3dft.h"

void	ft_init_game(t_game *game)
{
	ft_init_mlx(game);
	ft_init_player(game);
	ft_init_map(game);
	ft_fill_grid(game);
	ft_load_textures(game);
}

void	ft_render_background(t_game *game)
{
	ft_draw_ceiling(game);
	ft_draw_floor(game);
}

// Función principal de raycasting que recorre todos los rayos de la pantalla
void ft_raycast(t_game *game)
{
    double ray_angle;
    double ray_step;
    int x;

    ray_angle = game->player.dir - (FOV / 2);
    ray_step = FOV / (double)WIDTH;

    x = 0;
    while (x < WIDTH)
    {
        ft_cast_ray(game, x, ray_angle);
        ray_angle += ray_step;
        x++;
    }
}
