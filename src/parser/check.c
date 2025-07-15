/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:04:41 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/10 12:46:01 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

int	ft_check_surrounded(int **grid, int x, int y, t_numbers size)
{
	if (x == 0 || y == 0 || x == size.w - 1 || y == size.h - 1)
		return (ft_putstr_fd("Error: Map: not closed (border)\n", 2), 0);
	if (grid[y - 1][x] == -1)
		return (ft_putstr_fd("Error: Map: not closed (hole - up)\n", 2), 0);
	if (grid[y + 1][x] == -1)
		return (ft_putstr_fd("Error: Map: not closed (hole - down)\n", 2), 0);
	if (grid[y][x - 1] == -1)
		return (ft_putstr_fd("Error: Map: not closed (hole - left)\n", 2), 0);
	if (grid[y][x + 1] == -1)
		return (ft_putstr_fd("Error: Map: not closed (hole - right)\n", 2), 0);
	return (1);
}

int	ft_validate_walls(t_data *data)
{
	t_numbers	pos;
	t_numbers	size;
	int			**grid;

	grid = data->map.grid;
	size.w = data->map.width;
	size.h = data->map.height;
	pos.y = 0;
	while (pos.y < size.h)
	{
		pos.x = 0;
		while (pos.x < size.w)
		{
			if (grid[pos.y][pos.x] == 0)
				if (!ft_check_surrounded(grid, pos.x, pos.y, size))
					return (0);
			pos.x++;
		}
		pos.y++;
	}
	return (1);
}

int	ft_validate_player(t_data *data)
{
	if (data->player_x <= 0 || data->player_x >= data->map.width - 1
		|| data->player_y <= 0 || data->player_y >= data->map.height - 1)
		return (ft_putstr_fd("Error: Player: on map border\n", 2), 0);
	if (data->map.grid[data->player_y][data->player_x] != 0)
		return (ft_putstr_fd("Error: Player: not on walkable tile\n", 2), 0);
	return (1);
}

mlx_texture_t	*ft_validate_textures(const char *path, xpm_t **xpm_storage)
{
	const char	*ext;

	*xpm_storage = NULL;
	ext = ft_strrchr(path, '.');
	if (!ext)
	{
		ft_putstr_fd("Error: Texture: path has no extension: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	if (ft_strcmp(ext, ".png") != 0)
		return (ft_load_png(path));
	else if (ft_strcmp(ext, ".xpm") != 0 || ft_strcmp(ext, ".xpm42") != 0)
		return (ft_load_xpm(path, xpm_storage));
	else
	{
		ft_putstr_fd("Error: Textures: unsupported format: ", 2);
		ft_putstr_fd((char *)ext, 2);
		ft_putstr_fd(" (", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(")\n", 2);
		return (NULL);
	}
}

static int	ft_validate_tile(t_numbers *n, int **grid)
{
	if (n->x == 0 || n->y == 0 || n->x == n->w - 1 || n->y == n->h - 1)
	{
		ft_putstr_fd("Error: Map: not close (edge)\n", 2);
		return (0);
	}
	if (grid[n->y - 1][n->x] == -1 || grid[n->y + 1][n->x] == -1
		|| grid[n->y][n->x - 1] == -1 || grid[n->y][n->x + 1] == -1)
	{
		ft_putstr_fd("Error: Map: not close (hole)\n", 2);
		return (0);
	}
	return (1);
}

int	ft_validate_map(t_data *data)
{
	t_numbers	n;
	int			**grid;

	n.w = data->map.width;
	n.h = data->map.height;
	grid = data->map.grid;
	n.y = 0;
	while (n.y < n.h)
	{
		n.x = 0;
		while (n.x < n.w)
		{
			if (grid[n.y][n.x] == 0)
				if (!ft_validate_tile(&n, grid))
					return (0);
			n.x++;
		}
		n.y++;
	}
	return (1);
}
