/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:17:34 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/10 12:33:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

int	ft_parse_rgb(char *line)
{
	char			**parts;
	unsigned int	color;
	t_rgb			rgb;

	parts = ft_split(line, ',');
	if (!parts || ft_strlen_double(parts) != 3)
	{
		if (parts)
			ft_freedouble(parts);
		return (ft_putstr_fd("Error: Colors: not valid\n", 2), -1);
	}
	rgb.r = ft_atoi(parts[0]);
	rgb.g = ft_atoi(parts[1]);
	rgb.b = ft_atoi(parts[2]);
	if (rgb.r < 0 || rgb.r > 255
		|| rgb.g < 0 || rgb.g > 255
		|| rgb.b < 0 || rgb.b > 255)
	{
		ft_freedouble(parts);
		return (ft_putstr_fd("Error: Colors: out of range (0-255)\n", 2), -1);
	}
	color = (rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8) | 0xFF;
	ft_freedouble(parts);
	return (color);
}

int	ft_is_configuration(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
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

int	ft_parse_colors(char *line, t_data *data)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		data->floor = ft_parse_rgb(line + 2);
		if (!data->floor)
			return (0);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		data->ceiling = ft_parse_rgb(line + 2);
		if (!data->ceiling)
			return (0);
	}
	return (1);
}

int	ft_parse_configuration(char **lines, t_data *data)
{
	int	i;

	i = 0;
	while (lines[i] && ft_is_configuration(lines[i]))
	{
		if (!ft_parse_textures(lines[i], data))
			return (ft_putstr_fd("Error: Textures: not found\n", 2), 0);
		if (!ft_parse_colors(lines[i], data))
			return (ft_putstr_fd("Error: Colors: not found\n", 2), 0);
		i++;
	}
	return (1);
}
