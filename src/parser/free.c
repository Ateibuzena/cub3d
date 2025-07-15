/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/15 14:37:05 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

void	ft_free_xpm_textures(t_game *game)
{
	if (game->textures.north_xpm)
	{
		mlx_delete_xpm42(game->textures.north_xpm);
		game->textures.north_xpm = NULL;
		game->textures.north = NULL;
	}
	if (game->textures.south_xpm)
	{
		mlx_delete_xpm42(game->textures.south_xpm);
		game->textures.south_xpm = NULL;
		game->textures.south = NULL;
	}
	if (game->textures.east_xpm)
	{
		mlx_delete_xpm42(game->textures.east_xpm);
		game->textures.east_xpm = NULL;
		game->textures.east = NULL;
	}
	if (game->textures.west_xpm)
	{
		mlx_delete_xpm42(game->textures.west_xpm);
		game->textures.west_xpm = NULL;
		game->textures.west = NULL;
	}
}

void	ft_free_png_textures(t_game *game)
{
	if (!game->textures.north && !game->textures.south && !game->textures.east && !game->textures.west)
		return ;
	if (game->textures.north)
	{
		mlx_delete_texture(game->textures.north);
		game->textures.north = NULL;
	}
	if (game->textures.south)
	{
		mlx_delete_texture(game->textures.south);
		game->textures.south = NULL;
	}
	if (game->textures.east)
	{
		mlx_delete_texture(game->textures.east);
		game->textures.east = NULL;
	}
	if (game->textures.west)
	{
		mlx_delete_texture(game->textures.west);
		game->textures.west = NULL;
	}
}

void	ft_free_textures(t_game *game)
{
	ft_free_xpm_textures(game);
	ft_free_png_textures(game);
}

void	ft_free_paths(t_data *data)
{
	if (data->paths.north)
	{
		free(data->paths.north);
		data->paths.north = NULL;
	}
	if (data->paths.south)
	{
		free(data->paths.south);
		data->paths.south = NULL;
	}
	if (data->paths.east)
	{
		free(data->paths.east);
		data->paths.east = NULL;
	}
	if (data->paths.west)
	{
		free(data->paths.west);
		data->paths.west = NULL;
	}
}

void	ft_free_game(t_game *game, t_data *data, char **lines)
{
	if (lines)
		ft_freedouble(lines);
	if (data)
		ft_free_paths(data);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	ft_free_textures(game);
	if (game->map.grid)
		ft_freedouble_array(game->map.grid, game->map.height);
	if (game->mlx)
	{
		if (game->mlx->window)
			mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
}
