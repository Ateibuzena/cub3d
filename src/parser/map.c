#include "../../include/cub3dft.h"

int	ft_map_start(char **lines)
{
	int	i = 0;

	while (lines[i])
	{
		int j = 0;
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
	int	i = start;
	int	max_width = 0;

	while (lines[i])
	{
		int len = ft_strlen(lines[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	data->map.height = i - start;
	data->map.width = max_width;
}

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
			return (0);
		i++;
	}
	return (1);
}

int	ft_fill_map(char **lines, int start, t_data *data)
{
	int	y = 0;
	int	player_found = 0;

	while (y < data->map.height)
	{
		int x = 0;
		int i = 0;
		while (lines[start + y][i])
		{
			char c = lines[start + y][i];
			if (c == ' ')
				data->map.grid[y][x] = -1;
			else if (c == '1')
				data->map.grid[y][x] = 1;
			else if (c == '0')
				data->map.grid[y][x] = 0;
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (player_found)
					return (ft_putstr_fd("Error: múltiples jugadores\n", 2), 0);
				data->map.grid[y][x] = 0;
				data->player_x = x;
				data->player_y = y;
				data->player_dir = c;
				player_found = 1;
			}
			else
				return (ft_putstr_fd("Error: carácter inválido en el mapa\n", 2), 0);
			x++;
			i++;
		}
		// Rellenar el resto de la fila con -1
		while (x < data->map.width)
			data->map.grid[y][x++] = -1;
		y++;
	}
	if (!player_found)
		return (ft_putstr_fd("Error: jugador no encontrado\n", 2), 0);
	return (1);
}

int	ft_validate_map(t_data *data)
{
	int x, y;
	int w = data->map.width;
	int h = data->map.height;
	int **grid = data->map.grid;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			if (grid[y][x] == 0)
			{
				if (x == 0 || y == 0 || x == w - 1 || y == h - 1)
					return (ft_putstr_fd("Error: mapa no cerrado (borde)\n", 2), 0);
				if (grid[y - 1][x] == -1 || grid[y + 1][x] == -1 ||
					grid[y][x - 1] == -1 || grid[y][x + 1] == -1)
					return (ft_putstr_fd("Error: mapa no cerrado (agujero)\n", 2), 0);
			}
		}
	}
	return (1);
}
