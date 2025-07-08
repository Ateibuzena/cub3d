/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:00:45 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/08 15:01:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

static int	ft_compute_end(int start_y, float height)
{
	int	end_y;

	end_y = start_y + height;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	return (end_y);
}

static int	ft_compute_y(float height)
{
	int	start_y;

	start_y = (HEIGHT - height) / 2;
	if (start_y < 0)
		start_y = 0;
	return (start_y);
}

static int	ft_compute_texture(t_hit hit)
{
	int	tex_x;

	if (hit.face == 'N')
		tex_x = hit.tile_size - ((int)hit.x % hit.tile_size) - 1;
	else if (hit.face == 'S')
		tex_x = (int)hit.x % hit.tile_size;
	else if (hit.face == 'E')
		tex_x = (int)hit.y % hit.tile_size;
	else
		tex_x = hit.tile_size - ((int)hit.y % hit.tile_size) - 1;
	return (tex_x);
}

void	ft_render_wall(t_game *game, float ray_angle, int i)
{
	t_wall	wall;

	wall.hit = ft_cast_ray(game, ray_angle);
	wall.texture = ft_get_texture(game, wall.hit.face);
	wall.hit.tile_size = game->tile_size;
	if (!wall.texture || !wall.texture->pixels)
		return (ft_putstr_fd("Error: MLX42 failed to load texture\n", 2));
	wall.height = (wall.hit.tile_size / wall.hit.distance) * (WIDTH / (2
				* tan(FOV / 2)));
	wall.start_y = ft_compute_y(wall.height);
	wall.end_y = ft_compute_end(wall.start_y, wall.height);
	wall.tex_x = ft_compute_texture(wall.hit);
	ft_draw_wall(game, i, &wall);
}
