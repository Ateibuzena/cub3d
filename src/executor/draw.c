/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:22:35 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/08 14:29:36 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

void	ft_draw_point(t_numbers p, int size, int color, t_game *game)
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
