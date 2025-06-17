#include "../../include/cub3dft.h"

int	ft_load_textures(t_game *game, t_data data)
{
	game->textures.north = mlx_load_png(data.paths.north);
	game->textures.south = mlx_load_png(data.paths.south);
	game->textures.east = mlx_load_png(data.paths.east);
	game->textures.west = mlx_load_png(data.paths.west);

	if (!game->textures.north || !game->textures.south
		|| !game->textures.east || !game->textures.west)
		return (0);
	return (1);
}

mlx_texture_t *ft_get_texture(t_game *game, char face)
{
	if (face == 'N')
		return (game->textures.north);
	if (face == 'S')
		return (game->textures.south);
	if (face == 'E')
		return (game->textures.east);
	if (face == 'W')
		return (game->textures.west);
	return (NULL);
}

// Calcula step y tex_pos inicial para el mapeo de la textura en la pared
void ft_init_mapping(t_wall *wall)
{
	wall->step = (float)wall->texture->height / wall->height;
	wall->tex_pos = (wall->start_y - HEIGHT / 2 + wall->height / 2) * wall->step;
}

// Obtiene el color de la textura en la posición (tex_x, tex_y)
uint32_t ft_get_color(t_wall *wall, int tex_y)
{
	int			pixel_index;
	uint32_t	max_index;
	uint8_t		*p;
	uint32_t	color;

	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)wall->texture->height)
		tex_y = (int)wall->texture->height - 1;
	pixel_index = (tex_y * wall->texture->width + wall->tex_x) * 4;
	max_index = wall->texture->width * wall->texture->height * 4;
	if ((uint32_t)(pixel_index + 3) >= max_index)
	{
		fprintf(stderr, "Pixel index out of bounds: %d\n", pixel_index);
		return (0); // Color negro por defecto ante error
	}
	p = &wall->texture->pixels[pixel_index];
	color = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	return (color);
}

// Dibuja la columna vertical de la pared en la pantalla
void ft_draw_wall(t_game *game, int i, t_wall *wall)
{
	int y;
	int tex_y;
	uint32_t color;

	ft_init_mapping(wall);
	y = wall->start_y;
	while (y < wall->end_y)
	{
		tex_y = (int)wall->tex_pos;
		color = ft_get_color(wall, tex_y);
		mlx_put_pixel(game->img, i, y, color);
		wall->tex_pos += wall->step;
		y++;
	}
}
