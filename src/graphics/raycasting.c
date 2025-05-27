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

char	*ft_get_wall_direction(double dx, double dy)
{
	if (fabs(dx) > fabs(dy))
		return (dx > 0) ? "EAST" : "WEST";
	else
		return (dy > 0) ? "SOUTH" : "NORTH";
}

mlx_texture_t	*ft_get_texture(t_game *game, char *wall_dir)
{
	if (ft_strcmp(wall_dir, "NORTH"))
		return game->textures.north;
	if (ft_strcmp(wall_dir, "SOUTH"))
		return game->textures.south;
	if (ft_strcmp(wall_dir, "EAST"))
		return game->textures.east;
	if (ft_strcmp(wall_dir, "WEST"))
		return game->textures.west;
	return NULL;
}

void	ft_draw_vertical_strip(t_game *game, int x, t_ray ray, mlx_texture_t *texture, int tex_x)
{
	int		y = ray.start;
	int		texture_height = texture->height;
	int		texture_width = texture->width;
	uint8_t	*pixels = texture->pixels;
	int		bpp = 4;
	int		tex_y;
	int		pixel_index;

	while (y < ray.end)
	{
		if (y >= 0 && y < HEIGHT)
		{
			tex_y = ((y - ray.start) * texture_height) / ray.line_height;
			pixel_index = (tex_y * texture_width + tex_x) * bpp;
			if (pixel_index >= 0 && pixel_index + 3 < texture_width * texture_height * bpp)
			{
				uint32_t color =
					(pixels[pixel_index + 0] << 24) |
					(pixels[pixel_index + 1] << 16) |
					(pixels[pixel_index + 2] << 8) |
					(pixels[pixel_index + 3]);
				mlx_put_pixel(game->img, x, y, color);
			}
		}
		y++;
	}
}

void	ft_cast_single_ray(t_game *game, int x, double angle)
{
	t_ray	ray;

	ray.angle = angle;
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

	char *wall_dir = ft_get_wall_direction(ray.dx, ray.dy);
	mlx_texture_t *texture = ft_get_texture(game, wall_dir);

	if (!texture)
	{
		fprintf(stderr, "Error: texture not found for direction %s\n", wall_dir);
		return ;
	}

	int tex_x = (fabs(ray.dx) > fabs(ray.dy)) ? (int)fmod(ray.y, TILE_SIZE)
											  : (int)fmod(ray.x, TILE_SIZE);
	if (tex_x < 0)
		tex_x += TILE_SIZE;

	tex_x = (tex_x * texture->width) / TILE_SIZE;

	double corrected = ray.distance * cos(ray.angle - game->player.dir);
	ray.line_height = (int)((TILE_SIZE * HEIGHT) / corrected);
	ray.start = HEIGHT / 2 - ray.line_height / 2;
	ray.end = HEIGHT / 2 + ray.line_height / 2;

	ft_draw_vertical_strip(game, x, ray, texture, tex_x);
}

void	ft_raycast(t_game *game)
{
	double	ray_angle = game->player.dir - (FOV / 2);
	double	ray_step = FOV / (double)WIDTH;

	for (int x = 0; x < WIDTH; x++)
	{
		ft_cast_single_ray(game, x, ray_angle);
		ray_angle += ray_step;
	}
}
