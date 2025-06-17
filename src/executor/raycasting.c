#include "../../include/cub3dft.h"

// Inicializa dirección del rayo, posición en el mapa y delta_distancias
void ft_init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)(player->x / TILE_SIZE);
	ray->map_y = (int)(player->y / TILE_SIZE);
	ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

// Inicializa paso y distancia inicial al próximo lado (side_dist)
void ft_init_step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x * TILE_SIZE) / TILE_SIZE * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->map_x + 1) * TILE_SIZE - player->x) / TILE_SIZE * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y * TILE_SIZE) / TILE_SIZE * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->map_y + 1) * TILE_SIZE - player->y) / TILE_SIZE * ray->delta_dist_y;
	}
}

// Realiza una iteración del algoritmo DDA, avanza el rayo hasta que choca con un muro
void ft_perform_dda(t_ray *ray, t_game *game)
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
		if (ray->map_y >= 0 && ray->map_y < game->map.height
			&& ray->map_x >= 0 && ray->map_x < game->map.width
			&& game->map.grid[ray->map_y][ray->map_x] != 0)
		{
			ray->wall_type = game->map.grid[ray->map_y][ray->map_x]; // Guarda el tipo de muro
			break ;
		}
	}
}


// Calcula el punto de impacto y la distancia corregida para evitar fisheye
t_hit ft_calculate_hit(t_player *player, t_ray *ray, float ray_angle)
{
	t_hit hit;
	float wall_dist;

	if (ray->side == 0)
	{
		wall_dist = ((ray->map_x * TILE_SIZE - player->x) + (1 - ray->step_x) * TILE_SIZE / 2.0) / ray->ray_dir_x;
		hit.face = (ray->ray_dir_x > 0) ? 'W' : 'E';
	}
	else
	{
		wall_dist = ((ray->map_y * TILE_SIZE - player->y) + (1 - ray->step_y) * TILE_SIZE / 2.0) / ray->ray_dir_y;
		hit.face = (ray->ray_dir_y > 0) ? 'N' : 'S';
	}

	hit.x = player->x + wall_dist * ray->ray_dir_x;
	hit.y = player->y + wall_dist * ray->ray_dir_y;

	// Corregir distancia para evitar efecto fisheye
	hit.distance = wall_dist * cos(ray_angle - player->angle);
	if (hit.distance < 0.1)
		hit.distance = 0.1;

	return (hit);
}

// Función principal que usa las anteriores para realizar el raycast completo
t_hit ft_cast_ray(t_game *game, float ray_angle)
{
	t_ray ray;

	ft_init_ray(&ray, &game->player, ray_angle);
	ft_init_step(&ray, &game->player);
	ft_perform_dda(&ray, game);
	return (ft_calculate_hit(&game->player, &ray, ray_angle));
}
