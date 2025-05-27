#include "../../include/cub3dft.h"

// Verifica si la coordenada (x,y) corresponde a una pared en el mapa
int ft_is_wall(t_game *game, double x, double y)
{
    int map_x;
    int map_y;

    map_x = (int)(x / TILE_SIZE);
    map_y = (int)(y / TILE_SIZE);

    if (map_x < 0 || map_x >= game->map.width ||
        map_y < 0 || map_y >= game->map.height)
    {
        fprintf(stderr, "Error: Coordinates out of map bounds\n");
        return 1; // Consideramos fuera de mapa como pared para no salirnos
    }
    return game->map.grid[map_y][map_x];
}

// Calcula las dimensiones y posición vertical del strip a dibujar en pantalla
void ft_update_column(t_game *game, t_ray *ray)
{
    double corrected_distance;

    corrected_distance = ray->distance * cos(ray->angle - game->player.dir);
    ray->line_height = (int)((TILE_SIZE * HEIGHT) / corrected_distance);
    ray->start = HEIGHT / 2 - ray->line_height / 2;
    ray->end = HEIGHT / 2 + ray->line_height / 2;
}

// Detecta colisión con paredes verticales (líneas verticales del mapa)
int ft_cast_ray_vertical(t_game *game, t_ray *ray)
{
    double x = floor(ray->x / TILE_SIZE) * TILE_SIZE;
    if (ray->dx > 0)
        x += TILE_SIZE;

    double y = ray->y + (x - ray->x) * (ray->dy / ray->dx);
    double step_x = (ray->dx > 0) ? TILE_SIZE : -TILE_SIZE;
    double step_y = step_x * (ray->dy / ray->dx);

    while (1)
    {
        // Check boundaries antes de llamar a ft_is_wall
        int map_x = (int)((x + ((ray->dx > 0) ? 0 : -1)) / TILE_SIZE);
        int map_y = (int)(y / TILE_SIZE);

        if (map_x < 0 || map_x >= game->map.width ||
            map_y < 0 || map_y >= game->map.height)
        {
            // No print para evitar spam
            break; // fuera del mapa, detenemos búsqueda
        }

        if (ft_is_wall(game, x + ((ray->dx > 0) ? 0 : -1), y))
        {
            ray->x = x;
            ray->y = y;
            ray->distance = hypot(ray->x - game->player.x, ray->y - game->player.y);
            return 1;
        }

        x += step_x;
        y += step_y;

        // Si el rayo se ha ido demasiado lejos
        if (hypot(x - game->player.x, y - game->player.y) > 1000)
            break;
    }
    return 0;
}

// Detecta colisión con paredes horizontales (líneas horizontales del mapa)
int ft_cast_ray_horizontal(t_game *game, t_ray *ray)
{
    double y = floor(ray->y / TILE_SIZE) * TILE_SIZE;
    if (ray->dy > 0)
        y += TILE_SIZE;

    double x = ray->x + (y - ray->y) * (ray->dx / ray->dy);
    double step_y = (ray->dy > 0) ? TILE_SIZE : -TILE_SIZE;
    double step_x = step_y * (ray->dx / ray->dy);
    ray->distance = 0.0;

    while (1)
    {
        if (ft_is_wall(game, x, y + ((ray->dy > 0) ? 0 : -1)))
        {
            ray->x = x;
            ray->y = y;
            ray->distance = hypot(ray->x - game->player.x, ray->y - game->player.y);
            return 1; // colisión encontrada
        }
        x += step_x;
        y += step_y;

        if (ray->distance > 1000)
            break;
    }
    return 0;
}

void ft_cast_ray(t_game *game, int x, double angle)
{
    t_ray vert_ray;
    t_ray horiz_ray;
    t_ray *closest_ray;
    mlx_texture_t *texture;
    int tex_x;
    t_direction wall_dir;
    const char **directions = ft_get_directions_names();

    vert_ray.angle = horiz_ray.angle = angle;
    vert_ray.x = horiz_ray.x = game->player.x;
    vert_ray.y = horiz_ray.y = game->player.y;
    vert_ray.dx = horiz_ray.dx = cos(angle);
    vert_ray.dy = horiz_ray.dy = sin(angle);

    int vert_hit = ft_cast_ray_vertical(game, &vert_ray);
    int horiz_hit = ft_cast_ray_horizontal(game, &horiz_ray);

    if (!vert_hit && !horiz_hit)
        return; // no hay colisión

    // Escoge la colisión más cercana
    if (vert_hit && (!horiz_hit || vert_ray.distance < horiz_ray.distance))
    {
        closest_ray = &vert_ray;
        wall_dir = (vert_ray.dx > 0) ? EAST : WEST;
    }
    else
    {
        closest_ray = &horiz_ray;
        wall_dir = (horiz_ray.dy > 0) ? SOUTH : NORTH;
    }

    texture = ft_get_texture(game, wall_dir);

    if (!texture)
    {
        fprintf(stderr, "Error: texture not found for direction %s\n", directions[wall_dir]);
        return;
    }

    tex_x = ft_calculate_texture_x(closest_ray, texture);
    ft_update_column(game, closest_ray);
    ft_draw_column(game, x, *closest_ray, texture, tex_x);
}
