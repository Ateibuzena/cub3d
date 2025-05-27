#ifndef CUB3DFT_H
# define CUB3DFT_H

//libreries
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH 3840
# define HEIGHT 2160
# define FLOOR_COLOR 0x000000FF
# define CEILING_COLOR 0x000000FF
# define LINE_COLOR 0x0000FFFF
# define LILA_NEON 0xFF00FFFF
# define BLUE_NEON 0x0000FFFF

typedef struct s_pixel
{
	int x;
	int y;
}	t_pixel;

typedef struct s_perspective_metrics
{
	double	dx;
	double	dy;
	double	offset;
	double	spacing_normalized;
	double	nearest_line;
	double	threshold;
}	t_perspective_metrics;

typedef struct s_render_pixel
{
	int x;
	int y;
	int color;
}	t_render_pixel;

typedef struct s_perspective
{
	int origin_x;      // Punto de fuga X
	int origin_y;      // Punto de fuga Y
	int spacing;       // Espaciado entre líneas
	int floor_start;   // Límite de suelo (opcional si lo necesitas en Y)
}	t_perspective;

typedef struct s_ray
{
	double	angle;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	distance;
	int		line_height;
	int		start;
	int		end;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
}	t_player;

typedef struct s_map
{
    int	**grid;
    int	width;
    int	height;
}	t_map;

typedef struct s_textures
{
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *east;
    mlx_texture_t *west;
}	t_textures;


typedef struct s_game
{
    mlx_t			*mlx;
    mlx_image_t		*img;
    t_player		player;
	t_map			map;
	t_textures		textures;

}	t_game;

# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define TILE_SIZE 64
# define FOV (60 * (M_PI / 180)) // en radianes
# define STEP_SIZE 1.0

/*game.c*/
void			ft_init_game(t_game *game);
void			ft_render_background(t_game *game);

/*game_init.c*/
void			ft_init_mlx(t_game *game);
void			ft_init_player(t_game *game);
void			ft_init_map(t_game *game);
void			ft_fill_grid(t_game *game);
void			ft_load_textures(t_game *game);

/*mlx_render*/
int				ft_floor_x(int x, int y, t_perspective *perspective);
int				ft_floor_y(int x, int y, t_perspective *perspective);
void			ft_draw_ceiling(t_game *game);
void			ft_draw_floor(t_game *game);

/*raycasting.c*/
int				ft_is_wall(t_game *game, double x, double y);
void			ft_raycast(t_game *game);
void			ft_cast_single_ray(t_game *game, int x, double angle);
char			*ft_get_wall_direction(double dx, double dy);
mlx_texture_t	*ft_get_texture(t_game *game, char *wall_dir);
void			ft_draw_vertical_strip(t_game *game, int x, t_ray ray, mlx_texture_t *texture, int tex_x);

#endif