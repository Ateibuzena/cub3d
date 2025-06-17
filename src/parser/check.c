#include "../../include/cub3dft.h"

int	ft_validate_walls(t_data *data)
{
	int x, y;
	int w = data->map.width;
	int h = data->map.height;
	int **grid = data->map.grid;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
            fprintf(stderr, "%d ", grid[y][x]);
			if (grid[y][x] == 0)
			{
				// No puede estar en el borde
				if (x == 0 || y == 0 || x == w - 1 || y == h - 1)
					return (ft_putstr_fd("Error: Map: not closed (border)\n", 2), 0);

				// No puede estar junto a -1
				if (grid[y - 1][x] == -1)
                {
                    fprintf(stderr, "Error: arriba (%d, %d) = -1\n", y - 1, x);
                    return (ft_putstr_fd("Error: Map: not closed (hole - up)\n", 2), 0);
                }
                if (grid[y + 1][x] == -1)
                {
                    fprintf(stderr, "Error: abajo (%d, %d) = -1\n", y + 1, x);
                    return (ft_putstr_fd("Error: Map: not closed (hole - down)\n", 2), 0);
                }
                if (grid[y][x - 1] == -1)
                {
                    fprintf(stderr, "Error: izquierda (%d, %d) = -1\n", y, x - 1);
                    return (ft_putstr_fd("Error: Map: not closed (hole - left)\n", 2), 0);
                }
                if (grid[y][x + 1] == -1)
                {
                    fprintf(stderr, "Error: derecha (%d, %d) = -1\n", y, x + 1);
                    return (ft_putstr_fd("Error: Map: not closed (hole - right)\n", 2), 0);
                }

			}
		}
        write(1, "\n", 1);
	}
	return (1);
}

int	ft_validate_player(t_data *data)
{
	if (data->player_x <= 0 || data->player_x >= data->map.width - 1 ||
		data->player_y <= 0 || data->player_y >= data->map.height - 1)
		return (ft_putstr_fd("Error: Player on map border\n", 2), 0);
	if (data->map.grid[data->player_y][data->player_x] != 0)
		return (ft_putstr_fd("Error: Player not on walkable tile\n", 2), 0);
	return (1);
}
