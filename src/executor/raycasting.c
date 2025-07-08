/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:40:32 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/08 14:48:25 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

void	ft_init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)(player->x / player->tile_size);
	ray->map_y = (int)(player->y / player->tile_size);
	ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	ft_init_step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x * player->tile_size)
			/ player->tile_size * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->map_x + 1) * player->tile_size - player->x)
			/ player->tile_size * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y * player->tile_size)
			/ player->tile_size * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->map_y + 1) * player->tile_size - player->y)
			/ player->tile_size * ray->delta_dist_y;
	}
}

void	ft_perform_dda(t_ray *ray, t_game *game)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= 0 && ray->map_y < game->map.height && ray->map_x >= 0
			&& ray->map_x < game->map.width
			&& game->map.grid[ray->map_y][ray->map_x] != 0)
		{
			ray->wall_type = game->map.grid[ray->map_y][ray->map_x];
			break ;
		}
	}
}

t_hit	ft_calculate_hit(t_hit *hit, t_player *player, t_ray *ray, float angle)
{
	if (ray->side == 0)
	{
		hit->wall_dist = ((ray->map_x * player->tile_size - player->x) + (1
					- ray->step_x) * player->tile_size / 2.0) / ray->ray_dir_x;
		if (ray->ray_dir_x > 0)
			hit->face = 'W';
		else
			hit->face = 'E';
	}
	else
	{
		hit->wall_dist = ((ray->map_y * player->tile_size - player->y) + (1
					- ray->step_y) * player->tile_size / 2.0) / ray->ray_dir_y;
		if (ray->ray_dir_y > 0)
			hit->face = 'N';
		else
			hit->face = 'S';
	}
	hit->x = player->x + hit->wall_dist * ray->ray_dir_x;
	hit->y = player->y + hit->wall_dist * ray->ray_dir_y;
	hit->distance = hit->wall_dist * cos(angle - player->angle);
	if (hit->distance < 0.1)
		hit->distance = 0.1;
	return (*hit);
}

t_hit	ft_cast_ray(t_game *game, float ray_angle)
{
	t_ray	ray;
	t_hit	hit;

	ft_init_ray(&ray, &game->player, ray_angle);
	ft_init_step(&ray, &game->player);
	ft_perform_dda(&ray, game);
	return (ft_calculate_hit(&hit, &game->player, &ray, ray_angle));
}
