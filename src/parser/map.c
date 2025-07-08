/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:05:51 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/08 20:14:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

int	ft_alloc_grid(t_data *data)
{
	int	i;

	data->map.grid = malloc(sizeof(int *) * data->map.height);
	if (!data->map.grid)
		return (0);
	i = 0;
	while (i < data->map.height)
	{
		data->map.grid[i] = malloc(sizeof(int) * data->map.width);
		if (!data->map.grid[i])
		{
			while (--i >= 0)
				free(data->map.grid[i]);
			free(data->map.grid);
			data->map.grid = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_process_player(char c, t_data *data, t_numbers *n, int y)
{
	if (n->player_found)
		return (ft_putstr_fd("[❌] Player: multiplayers\n", 2), 0);
	data->map.grid[y][n->x] = 0;
	data->player_x = n->x;
	data->player_y = y;
	data->player_dir = c;
	n->player_found = 1;
	return (1);
}

static int	ft_process_cell(char c, t_data *data, t_numbers *n, int y)
{
	if (c == ' ')
		data->map.grid[y][n->x] = -1;
	else if (c == '1')
		data->map.grid[y][n->x] = 1;
	else if (c == '0')
		data->map.grid[y][n->x] = 0;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!ft_process_player(c, data, n, y))
			return (0);
	}
	else
		return (ft_putstr_fd("[❌] Player: syntax not valid\n", 2), 0);
	return (1);
}

static int	ft_fill_line(char *line, int y, t_data *data, t_numbers *n)
{
	char	c;

	n->x = 0;
	n->i = 0;
	while (line[n->i])
	{
		c = line[n->i];
		if (!ft_process_cell(c, data, n, y))
			return (0);
		n->x++;
		n->i++;
	}
	while (n->x < n->w)
	{
		data->map.grid[y][n->x] = -1;
		n->x++;
	}
	return (1);
}

int	ft_fill_map(char **lines, int start, t_data *data)
{
	t_numbers	numbers;

	numbers.w = data->map.width;
	numbers.h = data->map.height;
	numbers.y = 0;
	numbers.player_found = 0;
	while (numbers.y < numbers.h)
	{
		if (!ft_fill_line(lines[start + numbers.y], numbers.y, data, &numbers))
			return (0);
		numbers.y++;
	}
	if (!numbers.player_found)
		return (ft_putstr_fd("[❌] Player: not found\n", 2), 0);
	return (1);
}
