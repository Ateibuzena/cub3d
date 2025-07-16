/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:01:42 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/16 14:44:05 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

int	ft_load_textures(t_game *game, t_data data)
{
	game->textures.north = ft_validate_textures(data.paths.north,
			&game->textures.north_xpm);
	if (!game->textures.north)
		ft_putstr_fd("Error: Textures: Failed to load NORTH\n", 2);
	game->textures.south = ft_validate_textures(data.paths.south,
			&game->textures.south_xpm);
	if (!game->textures.south)
		ft_putstr_fd("Error: Textures: Failed to load SOUTH\n", 2);
	game->textures.east = ft_validate_textures(data.paths.east,
			&game->textures.east_xpm);
	if (!game->textures.east)
		ft_putstr_fd("Error: Textures: Failed to load EAST\n", 2);
	game->textures.west = ft_validate_textures(data.paths.west,
			&game->textures.west_xpm);
	if (!game->textures.west)
		ft_putstr_fd("Error: Textures: Failed to load WEST\n", 2);
	if (!game->textures.north || !game->textures.south || !game->textures.east
		|| !game->textures.west)
		return (0);
	game->tile_size = game->textures.north->width;
	return (1);
}

mlx_texture_t	*ft_get_texture(t_game *game, char face)
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

void	ft_init_mapping(t_wall *wall)
{
	wall->step = (float)wall->texture->height / wall->height;
	wall->tex_pos = (wall->start_y - HEIGHT / 2 + wall->height / 2)
		* wall->step;
}

uint32_t	ft_get_color(t_wall *wall, int tex_y)
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
		return (ft_putstr_fd("Error: Pixel: index out of bounds\n", 2), 0);
	p = &wall->texture->pixels[pixel_index];
	color = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	return (color);
}
