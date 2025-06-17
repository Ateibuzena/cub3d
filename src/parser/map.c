#include "../../include/cub3dft.h"

int	ft_is_map(char **lines)
{
	int i = 0;

	while (lines[i])
	{
		int j = 0;
		while (lines[i][j] == ' ')
			j++;
		if (lines[i][j] == '1')
			return (i);
		i++;
	}
	ft_putstr_fd("Error: Map: not found\n", 2);
	return (-1);
}

void		ft_get_dimensions(char **lines, int start, t_data *data)
{
	int	w;
	int	h;
	int	len;

	w = 0;
	h = 0;
	while (lines[start])
	{
		len = ft_strlen_nospace(lines[start]);
		if (len > w)
			w = len;
		h++;
		start++;
	}
	data->map.width = w;
	data->map.height = h;
}


int	ft_allocate_grid(char **lines, int start, t_data *data)
{
	int	i;
	int	j;
	int len;

	data->map.grid = malloc(data->map.height * sizeof(int *));
	if (!data->map.grid)
		return (ft_putstr_fd("Error: Map: malloc error\n", 2), 0);
	i = 0;
	while (i < data->map.height)
	{
		len = ft_strlen_nospace(lines[start + i]);
		data->map.grid[i] = malloc(data->map.width * sizeof(int));
		if (!data->map.grid[i])
		{
			ft_freedouble_array(data->map.grid, i);
			return (ft_putstr_fd("Error: Map: malloc error\n", 2), 0);
		}
		j = 0;
		while (j < data->map.width)
		{
			data->map.grid[i][j] = -1;
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_parse_map(char **lines, int start, t_data *data)
{
	int	i;
	char c;

	i = 0;
	while (i < data->map.height)
	{
		int j = 0;
		while (lines[start + i][j])
		{
			c = lines[start + i][j];
			if (c == ' ' || c == '\t' || c == '\n' || c == '0' || c == '1' ||
				c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				j++;
				continue ;
			}
			ft_freedouble_array(data->map.grid, data->map.height);
			return (ft_putstr_fd("Error: Map: not valid\n", 2), 0);
		}
		i++;
	}
	return (1);
}

int	ft_fill_grid(char **lines, int start, t_data *data)
{
	int i = 0;
	int player_found = 0;

	while (i < data->map.height)
	{
		int j = 0;
		while (lines[start + i][j])
		{
			char c = lines[start + i][j];

			/*if (c == ' ' || c == '\t' || c == '\n')
				data->map.grid[i][j] = -1;
			else */if (c == '1')
				data->map.grid[i][j] = 1;
			else if (c == '0')
				data->map.grid[i][j] = 0;
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (player_found)
					return (ft_putstr_fd("Error: multiple player positions\n", 2), 0);
				player_found = 1;
				data->map.grid[i][j] = 0;
				data->player_x = j;
				data->player_y = i;
				data->player_dir = c;
			}
			else
				data->map.grid[i][j] = -1;
			j++;
		}
		// rellena el resto de la fila con -1 si es más corta que data->map.width
		while (j < data->map.width)
			data->map.grid[i][j++] = -1;
		i++;
	}
	if (!player_found)
		return (ft_putstr_fd("Error: player not found\n", 2), 0);
	return (1);
}
