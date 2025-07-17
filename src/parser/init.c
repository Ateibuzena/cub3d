/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:57:21 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/17 12:12:58 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3dft.h"

void	ft_init_minimap(t_game *game)
{
	game->minimap.max_width = WIDTH / 4;
	game->minimap.max_height = HEIGHT / 4;
	game->minimap.tile_size = game->minimap.max_width / game->map.width;
	if (game->minimap.tile_size > game->minimap.max_height / game->map.height)
		game->minimap.tile_size = game->minimap.max_height / game->map.height;
	game->minimap.offset_x = 20;
	game->minimap.offset_y = game->minimap.offset_x * 2;
}

int	ft_init_map(char **lines, t_data *data, t_game *game)
{
	int	start;

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
	game->map = data->map;
	return (1);
}

int	ft_init_player(t_game *game, t_data *data)
{
	game->player.radius = game->tile_size * 0.1;
	game->player.x = (data->player_x * game->tile_size) + game->player.radius;
	game->player.y = (data->player_y * game->tile_size) + game->player.radius;
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
	game->player.tile_size = game->tile_size;
	if (!ft_validate_player(data) || !data->player_dir || data->player_x <= 0
		|| data->player_y <= 0)
	{
		ft_putstr_fd("Error: Player: position not valid\n", 2);
		return (0);
	}
	return (1);
}

int	ft_init_data(t_game *game, char **lines)
{
	t_data	data;

	if (!lines)
		return (ft_putstr_fd("Error: File: not readed\n", 2), 0);
	ft_memset(&data, 0, sizeof(t_data));
	if (!ft_parse_configuration(lines, &data, game))
		return (ft_free_game(game, &data, lines), 0);
	if (!ft_load_textures(game, data))
		return (ft_free_game(game, &data, lines), 0);
	if (!ft_init_map(lines, &data, game))
		return (ft_free_game(game, &data, lines), 0);
	if (!ft_init_player(game, &data))
		return (ft_free_game(game, &data, lines), 0);
	ft_init_minimap(game);
	return (ft_freedouble(lines), ft_free_paths(&data), 1);
}

void	ft_init_game(t_game *game, char *file)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
	{
		ft_putstr_fd("Error: MLX42: failed to initialize\n", 2);
		exit(EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		ft_putstr_fd("Error: MLX42: failed to create image\n", 2);
		ft_free_game(game, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		ft_putstr_fd("Error: MLX42: failed to display image\n", 2);
		ft_free_game(game, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	if (!ft_init_data(game, ft_read_file(file)))
		exit(EXIT_FAILURE);
}
