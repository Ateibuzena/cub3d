/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/15 15:40:41 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

int	ft_strlen_nospace(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			count++;
		i++;
	}
	return (count);
}

int	ft_map_start(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ' || lines[i][j] == '\t')
			j++;
		if (lines[i][j] == '1' || lines[i][j] == '0')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_map_dimensions(char **lines, int start, t_data *data)
{
	int	i;
	int	max_width;
	int	len;

	i = start;
	max_width = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	data->map.height = i - start;
	data->map.width = max_width;
}

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
