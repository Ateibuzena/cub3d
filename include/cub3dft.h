/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3dft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:54:56 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/22 23:24:59 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_map
{
	int		**grid;
	int		width;
	int		height;
	bool	show_map;
}	t_map;

typedef struct s_minimap
{
	int		tile_size;
	int		max_width;
	int		max_height;
	int		offset_x;
	int		offset_y;
}	t_minimap;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	float			radius;

	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;

	unsigned int	tile_size;
}	t_player;

# define FOV 1.57079632679

typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side; // 0 = vertical, 1 = horizontal
	int		wall_type;
}	t_ray;

typedef struct s_hit
{
	float			x;
	float			y;
	char			face; // 'N', 'S', 'E', 'W'
	float			distance;
	float			wall_dist;
	float			wall_height;
	int				wall_type;
	unsigned int	tile_size;
}	t_hit;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	xpm_t			*north_xpm;
	xpm_t			*south_xpm;
	xpm_t			*east_xpm;
	xpm_t			*west_xpm;
}	t_textures;

typedef struct s_wall
{
	mlx_texture_t	*texture;
	t_hit			hit;
	float			height;
	int				start_y;
	int				end_y;
	int				tex_x;
	float			step;
	float			tex_pos;
}	t_wall;

typedef struct s_paths
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
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
}	t_data;

# define WIDTH 3840
# define HEIGHT 2160

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			map;
	t_minimap		minimap;
	t_player		player;
	t_textures		textures;
	t_wall			wall;
	unsigned int	floor;
	unsigned int	ceiling;
	unsigned int	tile_size;
}	t_game;

/*init.c*/
int				ft_init_minimap(t_game *game);
int				ft_init_map(char **lines, t_data *data, t_game *game);
int				ft_init_player(t_game *game, t_data *data);
int				ft_init_data(t_game *game, char *file);
void			ft_init_game(t_game *game, char *file);
/*map.c*/
int				ft_alloc_grid(t_data *data);
int				ft_fill_map(char **lines, int start, t_data *data);

/*handler.c*/
void			ft_key_press(t_game *game, int key);
void			ft_key_release(t_game *game, int key);
void			ft_handle_key(mlx_key_data_t keydata, void *param);
int				ft_handle_loop(t_game *game);

/*draw.c*/
void			ft_draw_box(t_game *game, t_numbers p, int size, int color);
void			ft_draw_wall(t_game *game, int i, t_wall *wall);
void			ft_clear_image(t_game *game);
void			ft_draw_square(t_game *game, t_numbers p, int size, int color);
void			ft_draw_map(t_game *game);

/*color.c*/
unsigned int	ft_desaturate(unsigned int color, float factor);
unsigned int	ft_invert_color(unsigned int color);

/*render.c*/
void			ft_render_wall(t_game *game, float ray_angle, int i);

/*player.c*/
void			ft_rotate_player(t_game *game);
bool			ft_touch(float px, float py, t_game *game);
void			ft_move_direction(t_game *game, float dx, float dy);
void			ft_move_player(t_game *game);

/*raycasting.c*/
void			ft_init_ray(t_ray *ray, t_player *player, float ray_angle);
void			ft_init_step(t_ray *ray, t_player *player);
void			ft_perform_dda(t_ray *ray, t_game *game);
t_hit			ft_calculate_hit(t_hit *hit, t_player *player, t_ray *ray,
					float angle);
t_hit			ft_cast_ray(t_game *game, float ray_angle);

/*textures.c*/
int				ft_load_textures(t_game *game, t_data data);
mlx_texture_t	*ft_get_texture(t_game *game, char face);
void			ft_init_mapping(t_wall *wall);
uint32_t		ft_get_color(t_wall *wall, int tex_y);

/*read.c*/
char			**ft_read_file(char *path);
mlx_texture_t	*ft_load_png(const char *path);
mlx_texture_t	*ft_load_xpm(const char *path, xpm_t **xpm_storage);

/*graphics.c*/
int				ft_parse_rgb(char *line, unsigned int *color);
int				ft_is_configuration(char *line);
int				ft_parse_textures(char *line, t_data *data);
int				ft_parse_colors(char *line, t_data *data, t_game *game);
int				ft_parse_configuration(char **lines,
					t_data *data, t_game *game);

/*free.c*/
void			ft_free_xpm_textures(t_game *game);
void			ft_free_png_textures(t_game *game);
void			ft_free_textures(t_game *game);
void			ft_free_paths(t_data *data);
void			ft_free_game(t_game *game, t_data *data, char **lines);

/*utils.c*/
int				ft_strlen_nospace(char *str);
int				ft_map_start(char **lines);
void			ft_map_dimensions(char **lines, int start, t_data *data);
int				ft_check_surrounded(int **grid, int x, int y, t_numbers size);

/*check.c*/
int				ft_validate_walls(t_data *data);
int				ft_validate_player(t_data *data);
int				ft_validate_map(t_data *data);
mlx_texture_t	*ft_validate_textures(const char *path, xpm_t **xpm_storage);

#endif