#include "../../include/cub3dft.h"

int ft_calculate_texture_x(t_ray *ray, mlx_texture_t *texture)
{
    int tex_x;

    if (fabs(ray->dx) > fabs(ray->dy))
    {
        tex_x = (int)fmod(ray->y, TILE_SIZE);
        if (ray->dx > 0) // Invierte para la textura derecha
            tex_x = TILE_SIZE - tex_x - 1;
    }
    else
    {
        tex_x = (int)fmod(ray->x, TILE_SIZE);
        if (ray->dy < 0) // Invierte para la textura superior
            tex_x = TILE_SIZE - tex_x - 1;
    }

    if (tex_x < 0)
        tex_x += TILE_SIZE;

    return (tex_x * texture->width) / TILE_SIZE;
}

// Dibuja una columna vertical (strip) de la pared con textura en la imagen
void ft_draw_column(t_game *game, int x, t_ray ray, mlx_texture_t *texture, int tex_x)
{
    int y;
    int tex_y;
    unsigned int pixel_index;
    const int bpp = 4; // bytes per pixel RGBA
    uint32_t color;

    y = ray.start;
    while (y < ray.end)
    {
        if (y >= 0 && y < HEIGHT)
        {
            tex_y = ((y - ray.start) * texture->height) / ray.line_height;
            pixel_index = (tex_y * texture->width + tex_x) * bpp;

            // Asegurar que no se salga del buffer de la textura
            if (pixel_index + 3 < texture->width * texture->height * bpp)
            {
                color = (texture->pixels[pixel_index + 0] << 24) |
                        (texture->pixels[pixel_index + 1] << 16) |
                        (texture->pixels[pixel_index + 2] << 8)  |
                        (texture->pixels[pixel_index + 3]);

                mlx_put_pixel(game->img, x, y, color);
            }
        }
        y++;
    }
}
