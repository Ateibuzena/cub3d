#include "../../include/cub3dft.h"

void    ft_draw_square(int x, int y, int size, int color, t_game *game)
{
    int i;

    i = 0;
    while (i < size)
    {
        mlx_put_pixel(game->img, x + i, y, color);
        i++;
    }
    i = 0;
    while (i < size)
    {
        mlx_put_pixel(game->img, x, y + i, color);
        i++;
    }
    i = 0;
    while (i < size)
    {
        mlx_put_pixel(game->img, x + size, y + i, color);
        i++;
    }
    i = 0;
    while (i < size)
    {
        mlx_put_pixel(game->img, x + i, y + size, color);
        i++;
    }
}

void	ft_clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, game->ceiling); // cielo (azul claro)
			else
				mlx_put_pixel(game->img, x, y, game->floor); // suelo (verde oscuro)
			x++;
		}
		y++;
	}
}
