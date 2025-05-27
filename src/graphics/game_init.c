#include "../../include/cub3dft.h"

int world_map[MAP_HEIGHT][MAP_WIDTH] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1},
};
	
void	ft_init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
	{
		fprintf(stderr, "Error: MLX42 failed to initialize\n");
		exit(EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		fprintf(stderr, "Error: MLX42 failed to create image\n");
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_player(t_game *game)
{
	game->player.x = TILE_SIZE * 2.5;
	game->player.y = TILE_SIZE * 2.5;
	game->player.dir = M_PI / 2; // 90º mirando hacia abajo
}

void	ft_init_map(t_game *game)
{
	int	y;

	game->map.width = MAP_WIDTH;
	game->map.height = MAP_HEIGHT;
	game->map.grid = malloc(MAP_WIDTH * sizeof(int *));
	if (!game->map.grid)
	{
		mlx_close_window(game->mlx);
		fprintf(stderr, "Error: Memory allocation failed for map grid\n");
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (y < MAP_HEIGHT)
	{
		game->map.grid[y] = malloc(MAP_WIDTH * sizeof(int));
		if (!game->map.grid[y])
		{
			while (y > 0)
				free(game->map.grid[--y]);
			free(game->map.grid);
			mlx_close_window(game->mlx);
			fprintf(stderr, "Error: Memory allocation failed for map row\n");
			mlx_terminate(game->mlx);
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

void	ft_fill_grid(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			game->map.grid[y][x] = world_map[y][x];
			x++;
		}
		y++;
	}
}

void	ft_load_textures(t_game *game)
{
	game->textures.north = mlx_load_png("textures/wall_north.png");
	game->textures.south = mlx_load_png("textures/wall_south.png");
	game->textures.east = mlx_load_png("textures/wall_east.png");
	game->textures.west = mlx_load_png("textures/wall_west.png");

	if (!game->textures.north || !game->textures.south
		|| !game->textures.east || !game->textures.west)
	{
		fprintf(stderr, "Error: No se pudieron cargar una o más texturas.\n");
		exit(EXIT_FAILURE);
	}
}
