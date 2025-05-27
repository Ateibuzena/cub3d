#include "../../include/cub3dft.h"

// Array estático de nombres para las direcciones, accesible globalmente
const char **ft_get_directions_names(void)
{
    static const char *names[DIRECTION_COUNT] = {
        "NORTH",
        "SOUTH",
        "EAST",
        "WEST"
    };
    return names;
}

// Devuelve la dirección de la pared según el vector del impacto (dx, dy)
t_direction ft_get_wall_direction(double dx, double dy)
{
    if (fabs(dx) > fabs(dy))
    {
        if (dx > 0)
            return EAST;
        else
            return WEST;
    }
    else
    {
        if (dy > 0)
            return SOUTH;
        else
            return NORTH;
    }
}

// Obtiene la textura correspondiente según la dirección de la pared
mlx_texture_t *ft_get_texture(t_game *game, t_direction dir)
{
    if (dir == NORTH)
        return game->textures.north;
    else if (dir == SOUTH)
        return game->textures.south;
    else if (dir == EAST)
        return game->textures.east;
    else if (dir == WEST)
        return game->textures.west;
    else
        return NULL;
}
