#include "../../include/cub3dft.h"

int	ft_parse_rgb(char *line)
{
	char	**parts;
	int		r, g, b;
	unsigned int color;

	parts = ft_split(line, ',');
	if (!parts || ft_strlen_double(parts) != 3)
		return (ft_putstr_fd("Error: Color: not valid\n", 2), -1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_putstr_fd("Error: Color: out of range (0-255)\n", 2), -1);
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	ft_freedouble(parts);
	return (color);
}

int ft_is_configuration(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
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
	int i = 0;

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
