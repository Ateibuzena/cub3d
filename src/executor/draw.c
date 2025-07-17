/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:22:35 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/17 12:51:45 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

void	ft_draw_box(t_game *game, t_numbers p, int size, int color)
{
	int	i;

	i = 0;
	while (i < size)
		mlx_put_pixel(game->img, p.x + i++, p.y, color);
	i = 0;
	while (i < size)
		mlx_put_pixel(game->img, p.x, p.y + i++, color);
	i = 0;
	while (i < size)
		mlx_put_pixel(game->img, p.x + size, p.y + i++, color);
	i = 0;
	while (i < size)
		mlx_put_pixel(game->img, p.x + i++, p.y + size, color);
}

void	ft_draw_wall(t_game *game, int i, t_wall *wall)
{
	int			y;
	int			tex_y;
	uint32_t	color;

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
				mlx_put_pixel(game->img, x, y, game->ceiling);
			else
				mlx_put_pixel(game->img, x, y, game->floor);
			x++;
		}
		y++;
	}
}

void	ft_draw_square(t_game *game, t_numbers p, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(game->img, p.x + i, p.y + j, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_game *game)
{
	t_numbers		p;
	unsigned int	wall_color;
	unsigned int	player_color;

	player_color = ft_invert_color(ft_desaturate(game->floor, 0.1f));
	wall_color = ft_invert_color(game->floor);
	p.i = 0;
	while (p.i < game->map.height)
	{
		p.j = 0;
		while (p.j < game->map.width)
		{
			p.x = game->minimap.offset_x + p.j * game->minimap.tile_size;
			p.y = game->minimap.offset_y + p.i * game->minimap.tile_size;
			if (game->map.grid[p.i][p.j] == 1)
				ft_draw_square(game, p, game->minimap.tile_size, wall_color);
			p.j++;
		}
		p.i++;
	}
	p.x = game->minimap.offset_x + (int)(game->player.x / game->tile_size)
		* game->minimap.tile_size;
	p.y = game->minimap.offset_y + (int)(game->player.y / game->tile_size)
		* game->minimap.tile_size;
	ft_draw_square(game, p, game->minimap.tile_size, player_color);
}
