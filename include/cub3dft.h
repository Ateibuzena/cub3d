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
# define LINE_COLOR 0xFF00FFFF

typedef struct s_perspective_params
{
	int	point_x;
	int	point_y;
	int	spacing;
	int	floor_start;
}	t_perspective_params;

typedef struct s_perspective_calc
{
	double	dx;
	double	dy;
	double	offset;
	double	spacing_normalized;
	double	nearest_line;
	double	threshold;
}	t_perspective_calc;

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


typedef struct s_game
{
    mlx_t		*mlx;
    mlx_image_t	*img;
    t_player	player;
	t_map		map;

}	t_game;

# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define TILE_SIZE 64
# define FOV (60 * (M_PI / 180)) // en radianes
# define STEP_SIZE 1.0

/*mlx_init.c*/
void	ft_init_window(t_game *game);

/*mlx_render*/
void	ft_render_background(t_game *game);

/*raycasting.c*/
int		ft_is_wall(t_game *game, double x, double y);
void	ft_raycast(t_game *game);

#endif