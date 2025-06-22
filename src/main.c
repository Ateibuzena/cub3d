#include "../include/cub3dft.h"

int	ft_init_map(char **lines, t_data *data)
{
	int start;
	
	start = ft_map_start(lines);
	if (start == -1)
		return (ft_putstr_fd("Error: Map: not found\n", 2), 0);
	ft_map_dimensions(lines, start, data);
	if (!ft_alloc_grid(data))
		return (ft_putstr_fd("Error: Map: malloc failed\n", 2), 0);
	if (!ft_fill_map(lines, start, data))
	{
		ft_freedouble_array(data->map.grid, data->map.height);
		data->map.grid = NULL;
		ft_putstr_fd("Error: Map: failed to fill map\n", 2);
		return (0);
	}
	if (!ft_validate_map(data))
	{
		ft_freedouble_array(data->map.grid, data->map.height);
		data->map.grid = NULL;
		ft_putstr_fd("Error: Map: not valid\n", 2);
		return (0);
	}
	return (1);
}

int ft_init_player(t_game *game, t_data *data)
{
    game->player.x = (data->player_x * TILE_SIZE) + PLAYER_RADIUS;
    game->player.y = (data->player_y * TILE_SIZE) + PLAYER_RADIUS;
    if (data->player_dir == 'E')
        game->player.angle = 0;
    if (data->player_dir == 'S')
        game->player.angle = M_PI / 2;
    if (data->player_dir == 'W')
        game->player.angle = M_PI;
    if (data->player_dir == 'N')
        game->player.angle = 3 * M_PI / 2;
    game->player.key_up = false;
    game->player.key_down = false;
    game->player.key_right = false;
    game->player.key_left = false;
    game->player.left_rotate = false;
    game->player.right_rotate = false;
    game->floor = data->floor;
    game->ceiling = data->ceiling;
	if (!ft_validate_player(data) || !data->player_dir || data->player_x <= 0 || data->player_y <= 0)
	{
		ft_putstr_fd("Error: Player position not valid\n", 2);
		return (0);
	}
	return (1);
}

int	ft_init_data(t_game *game, char *path)
{
	char	**lines;
	t_data	data;

	fprintf(stderr, "\nReading file: %s\n", path);
	lines = ft_read_file(path);
	if (!lines)
		return (ft_putstr_fd("Error: File: not readed\n", 2), 0);
	fprintf(stderr, "\nFile readed successfully\n");

	fprintf(stderr, "\nParsing configuration section\n");
	if (!ft_parse_configuration(lines, &data))
	{
		ft_freedouble(lines);
		ft_free_paths(&data);
		ft_putstr_fd("Error: MLX42 failed to parse configuration section\n", 2);
		return (0);
	}
	fprintf(stderr, "\nConfiguration parsed successfully\n");

	fprintf(stderr, "\nLoading textures\n");
	if (!ft_load_textures(game, data))
	{
		ft_freedouble(lines);
		ft_free_paths(&data);
		ft_free_textures(game);
		ft_putstr_fd("MLX42: failed to load texture\n", 2);
		return (0);
	}
	fprintf(stderr, "\nTextures loaded successfully\n");

	fprintf(stderr, "\nInitializing map\n");
	if (!ft_init_map(lines, &data))
	{
		ft_freedouble(lines);
		ft_free_paths(&data);
		ft_free_textures(game);
		ft_putstr_fd("Error: MLX42 failed to parse map section\n", 2);
		return (0);
	}
	game->map = data.map;
	fprintf(stderr, "\nMap initialized successfully: width=%d, height=%d\n", game->map.width, game->map.height);
	
	fprintf(stderr, "\nInitializing player\n");
	if (!ft_init_player(game, &data))
	{
		ft_freedouble(lines);
		ft_freedouble_array(data.map.grid, data.map.height);
		ft_free_paths(&data);
		ft_free_textures(game);
		ft_putstr_fd("Error: MLX42 failed to create player\n", 2);
		return (0);
	}
	fprintf(stderr, "\nPlayer initialized successfully: x=%f, y=%f, angle=%f\n", 
		game->player.x, game->player.y, game->player.angle);
	
	ft_freedouble(lines);
	ft_free_paths(&data);
	return (1);
}

void	ft_init_game(t_game *game, char *file)
{
	fprintf(stderr, "\nInitializing game\n");
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
	{
		ft_putstr_fd("Error: MLX42: failed to initialize\n", 2);
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "\nMLX42 initialized successfully\n");

	fprintf(stderr, "\nCreating image with dimensions: %dx%d\n", WIDTH, HEIGHT);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		ft_putstr_fd("Error: MLX42: failed to create image\n", 2);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "\nImage created successfully\n");

	fprintf(stderr, "\nLoading image to window\n");
    if(mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		ft_putstr_fd("Error: MLX42: failed to display image\n", 2);
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "\nImage displayed successfully\n");

	if (!ft_init_data(game, file))
	{
		mlx_close_window(game->mlx);
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	ft_init_game(&game, argv[1]);
	mlx_key_hook(game.mlx, (void *)ft_handle_key, &game);

	//ft_draw_square(WIDTH / 2, HEIGHT / 2, TILE_SIZE, 0x00FF00FF, &game);
	mlx_loop_hook(game.mlx, (void *)ft_handle_loop, &game);
	
	mlx_loop(game.mlx);

	mlx_close_window(game.mlx);
	mlx_delete_image(game.mlx, game.img);
	ft_free_textures(&game);
	ft_freedouble_array(game.map.grid, game.map.height);
	mlx_terminate(game.mlx);
	
	ft_putstr_fd("\nGame terminated successfully\n", 1);
	return (0);
}
