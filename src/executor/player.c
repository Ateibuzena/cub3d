/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:33:15 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/08 14:35:32 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

void	ft_rotate_player(t_game *game)
{
	float	angle_speed;

	angle_speed = (0.1);
	if (game->player.left_rotate)
		game->player.angle -= angle_speed;
	if (game->player.right_rotate)
		game->player.angle += angle_speed;
	if (game->player.angle > 2 * M_PI)
		game->player.angle -= 2 * M_PI;
	if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
}

bool	ft_touch(float px, float py, t_game *game)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)(px / game->tile_size);
	cell_y = (int)(py / game->tile_size);
	return (game->map.grid[cell_y][cell_x] == 0);
}

static bool	ft_can_move_to(float x, float y, t_game *game)
{
	return (ft_touch(x - game->player.radius, y - game->player.radius, game)
		&& ft_touch(x + game->player.radius, y - game->player.radius, game)
		&& ft_touch(x - game->player.radius, y + game->player.radius, game)
		&& ft_touch(x + game->player.radius, y + game->player.radius, game));
}

void	ft_move_direction(t_game *game, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	if (ft_can_move_to(new_x, game->player.y, game))
		game->player.x = new_x;
	if (ft_can_move_to(game->player.x, new_y, game))
		game->player.y = new_y;
}

void	ft_move_player(t_game *game)
{
	float	speed;
	float	cos_angle;
	float	sin_angle;

	speed = (game->tile_size * 0.2);
	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	ft_rotate_player(game);
	if (game->player.key_up)
		ft_move_direction(game, cos_angle * speed, sin_angle * speed);
	if (game->player.key_down)
		ft_move_direction(game, -cos_angle * speed, -sin_angle * speed);
	if (game->player.key_left)
		ft_move_direction(game, sin_angle * speed, -cos_angle * speed);
	if (game->player.key_right)
		ft_move_direction(game, -sin_angle * speed, cos_angle * speed);
}
