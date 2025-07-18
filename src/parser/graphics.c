/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:17:34 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/16 16:22:30 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

int	ft_is_configuration(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return ('T');
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return ('C');
	return (0);
}

int	ft_parse_rgb(char *line, unsigned int *color)
{
	char	**parts;
	t_rgb	rgb;

	parts = ft_split(line, ',');
	if (!parts || ft_strlen_double(parts) != 3)
	{
		if (parts)
			ft_freedouble(parts);
		ft_putstr_fd("Error: Colors: not valid\n", 2);
		return (0);
	}
	rgb.r = ft_atoi(parts[0]);
	rgb.g = ft_atoi(parts[1]);
	rgb.b = ft_atoi(parts[2]);
	ft_freedouble(parts);
	if (rgb.r < 0 || rgb.r > 255
		|| rgb.g < 0 || rgb.g > 255
		|| rgb.b < 0 || rgb.b > 255)
	{
		ft_putstr_fd("Error: Colors: out of range (0-255)\n", 2);
		return (0);
	}
	*color = (rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8) | 0xFF;
	return (1);
}

int	ft_parse_colors(char *line, t_data *data, t_game *game)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!ft_parse_rgb(line + 2, &data->floor))
			return (0);
		game->floor = data->floor;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!ft_parse_rgb(line + 2, &data->ceiling))
			return (0);
		game->ceiling = data->ceiling;
	}
	return (1);
}

int	ft_parse_textures(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		data->paths.north = ft_strclean(line + 3, '\n');
		if (!data->paths.north)
			return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		data->paths.south = ft_strclean(line + 3, '\n');
		if (!data->paths.south)
			return (0);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		data->paths.west = ft_strclean(line + 3, '\n');
		if (!data->paths.west)
			return (0);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		data->paths.east = ft_strclean(line + 3, '\n');
		if (!data->paths.east)
			return (0);
	}
	return (1);
}

int	ft_parse_configuration(char **lines, t_data *data, t_game *game)
{
	int	i;
	int	colors;
	int	textures;

	i = -1;
	colors = 0;
	textures = 0;
	while (lines[++i])
	{
		if (ft_is_configuration(lines[i]) == 'T'
			&& ft_parse_textures(lines[i], data))
			textures += 1;
		else if (ft_is_configuration(lines[i]) == 'C'
			&& ft_parse_colors(lines[i], data, game))
			colors += 1;
	}
	if (textures < 4)
		return (ft_putstr_fd("Error: Textures: not found\n", 2), 0);
	else if (textures > 4)
		return (ft_putstr_fd("Error: Textures: found to much\n", 2), 0);
	if (colors < 2)
		return (ft_putstr_fd("Error: Colors: not found\n", 2), 0);
	else if (colors > 2)
		return (ft_putstr_fd("Error: Colors: found to much\n", 2), 0);
	return (1);
}
