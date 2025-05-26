#include "../../include/cub3dft.h"

int	ft_is_wall(t_game *game, double x, double y)
{
    int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);

	if (map_x < 0 || map_x >= game->map.width
			|| map_y < 0 || map_y >= game->map.height)
	{
		fprintf(stderr, "Error: Coordinates out of map bounds\n");
		return (1);
	}
	return (game->map.grid[map_y][map_x]);
}

void	ft_raycast(t_game *game)
{
	t_ray	ray;
	double	ray_step;
	double	corrected;

	ray.angle = game->player.dir - (FOV / 2);
	ray_step = FOV / (double)WIDTH;

	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		ray.x = game->player.x;
		ray.y = game->player.y;
		ray.dx = cos(ray.angle);
		ray.dy = sin(ray.angle);
		ray.distance = 0;
		while (!ft_is_wall(game, ray.x, ray.y) && ray.distance < 1000)
		{
			ray.x += ray.dx * STEP_SIZE;
			ray.y += ray.dy * STEP_SIZE;
			ray.distance += STEP_SIZE;
		}
		corrected = ray.distance * cos(ray.angle - game->player.dir);
		ray.line_height = (int)((TILE_SIZE * HEIGHT) / corrected);
		ray.start = HEIGHT / 2 - ray.line_height / 2;
		ray.end = HEIGHT / 2 + ray.line_height / 2;
		
		y = ray.start;
		while (y < ray.end)
		{
			if (y >= 0 && y < HEIGHT)
				mlx_put_pixel(game->img, x, y, 0xFFB57EDC);
			y++;
		}
		ray.angle += ray_step;
		x++;
	}
}