#ifndef CUB3DFT_H
# define CUB3DFT_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>

# define GOLD_NEON      0xFFD700FF  // (glod)
# define GREY_NEON      0xA9A9A9FF  // (grey)
# define WHITE_NEON     0xFFFFFFFF  // (white)
# define LIME_NEON      0xBFFF00FF  // (green lemon)
# define VIOLET_NEON    0x8A2BE2FF  // (neon purple)
# define PINK_NEON      0xFF69B4FF  // (hot pink)

# define AQUA		    0x7FFFD4FF  // (water)
# define SKYBLUE		0x87CEFAFF  // (blue sky)
# define MAGENTA		0xFF00FFFF  // (neon fucsia)
# define CYAN		    0x00FFFFFF  // (neon cian)
# define ORANGE    		0xFFA500FF  // (orange)
# define BLUE 			0x0000FFFF  // (blue)
# define YELLOW			0xFFFF00FF  // (yellow)
# define GREEN 			0x00FF00FF  // (green)
# define BLACK 			0x000000FF  // (black)
# define RED 			0xFF0000FF  // (red)
# define VIOLET  		0x4B0082FF  // (purple)

# define M_PI 3.14159265358979323846

# define TILE_SIZE 1400

typedef struct s_map
{
    int		**grid;
    int		width;
    int		height;
}	t_map;

#define PLAYER_RADIUS (TILE_SIZE * 0.1)

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;


# define FOV (M_PI / 2)

typedef struct s_ray
{
	float ray_dir_x;
	float ray_dir_y;
	float delta_dist_x;
	float delta_dist_y;
	float side_dist_x;
	float side_dist_y;
	int step_x;
	int step_y;
	int map_x;
	int map_y;
	int side; // 0 = vertical, 1 = horizontal
	int wall_type;
}	t_ray;

typedef struct s_hit
{
	float x;
	float y;
	char  face; // 'N', 'S', 'E', 'W'
	float distance;
	float wall_height;
	int	wall_type;
}	t_hit;

/*-------------OPCIONAL--------------*/

# define LINE_FLOOR BLACK_NEON
# define LINE_CEILING BLACK_NEON
# define VANISH_Y (HEIGHT / 2)
# define GRID_SPACING 48
# define BG_NONE    0
# define BG_FLOOR   1
# define BG_CEILING 2

typedef struct s_background
{
	int		origin_x;
	int		origin_y;
	int		area;
	int		color;
}	t_background;


/*background.c*/
//void			ft_draw_background(t_game *game, int area);
//void			ft_draw_horizontal(t_background *ctx, t_game *game);
//void			ft_draw_radial(t_background *ctx, double dx, double dy, t_game *game);
//void			ft_draw_vertical(t_background *ctx, t_game *game);

/*-----------------------------------*/

typedef struct s_textures
{
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *east;
    mlx_texture_t *west;
}	t_textures;

typedef struct s_wall
{
    t_hit           hit;
    mlx_texture_t  *texture;
    float           height;
    int             start_y;
    int             end_y;
    int             tex_x;
    float           step;
    float           tex_pos;
}   t_wall;

typedef struct s_paths
{
	char *north;
	char *south;
	char *west;
	char *east;
}	t_paths;

typedef struct s_data
{
    t_map			map;
	t_paths			paths;
	unsigned int	floor;
	unsigned int	ceiling;
	int				player_x;
	int				player_y;
	char			player_dir;
}   t_data;

# define WIDTH 3840
# define HEIGHT 2160

typedef struct s_game
{
    mlx_t			*mlx;
    mlx_image_t		*img;
	t_map			map;
	t_player		player;
	t_textures		textures;
	t_wall			wall;
	unsigned int	floor;
	unsigned int	ceiling;
}	t_game;

/*main.c*/
int				ft_init_map(char **lines, t_data *data);
int 			ft_init_player(t_game *game, t_data *data);
int				ft_init_data(t_game *game, char *path);
void			ft_init_game(t_game *game, char *file);

/*map.c*/
int				ft_map_start(char **lines);
void			ft_map_dimensions(char **lines, int start, t_data *data);
int				ft_alloc_grid(t_data *data);
int				ft_fill_map(char **lines, int start, t_data *data);
int				ft_validate_map(t_data *data);

/*handler.c*/
void 			ft_key_press(t_game *game, int key);
void 			ft_key_release(t_game *game, int key);
void 			ft_handle_key(mlx_key_data_t keydata, void *param);
int				ft_handle_loop(t_game *game);

/*draw.c*/
void    		ft_draw_square(int x, int y, int size, int color, t_game *game);
void			ft_clear_image(t_game *game);

/*render.c*/
void			ft_render_wall(t_game *game, float ray_angle, int i);

/*player.c*/
void 			ft_rotate_player(t_game *game);
bool    		ft_touch(float px, float py, t_game *game);
void 			ft_move_direction(t_game *game, float dx, float dy);
void 			ft_move_player(t_game *game);

/*raycasting.c*/
void 			ft_init_ray(t_ray *ray, t_player *player, float ray_angle);
void 			ft_init_step(t_ray *ray, t_player *player);
void 			ft_perform_dda(t_ray *ray, t_game *game);
t_hit 			ft_calculate_hit(t_player *player, t_ray *ray, float ray_angle);
t_hit 			ft_cast_ray(t_game *game, float ray_angle);

/*textures.c*/
int				ft_load_textures(t_game *game, t_data data);
mlx_texture_t	*ft_get_texture(t_game *game, char face);
void 			ft_init_mapping(t_wall *wall);
uint32_t		ft_get_color(t_wall *wall, int tex_y);
void			ft_draw_wall(t_game *game, int i, t_wall *wall);

/*read.c*/
char			**ft_read_file(char *path);

/*graphics.c*/
int				ft_parse_rgb(char *line);
int				ft_is_configuration(char *line);
int				ft_parse_textures(char *line, t_data *data);
int				ft_parse_colors(char *line, t_data *data);
int				ft_parse_configuration(char **lines, t_data *data);

/*utils.c*/
int				ft_strlen_nospace(char *str);

/*check.c*/
int				ft_validate_walls(t_data *data);
int				ft_validate_player(t_data *data);

void	ft_free_textures(t_game *game);
void	ft_free_paths(t_data *data);

#endif