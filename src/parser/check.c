#include "../../include/cub3dft.h"

int	ft_validate_walls(t_data *data)
{
	t_numbers	n;
	t_numbers	s;

	int **grid;
	
	grid = data->map.grid;
	s.w = data->map.width;
	s.h = data->map.height;
	n.y = 0;
	while (n.y < s.h)
	{
		n.x = 0;
		while (n.x < s.w)
		{
			if (grid[n.y][n.x] == 0)
			{
				if (n.x == 0 || n.y == 0 || n.x == s.w - 1 || n.y == s.h - 1)
					return (ft_putstr_fd("Error: Map: not closed (border)\n", 2), 0);
				if (grid[n.y - 1][n.x] == -1)
                    return (ft_putstr_fd("Error: Map: not closed (hole - up)\n", 2), 0);
                if (grid[n.y + 1][n.x] == -1)
                    return (ft_putstr_fd("Error: Map: not closed (hole - down)\n", 2), 0);
                if (grid[n.y][n.x - 1] == -1)
                    return (ft_putstr_fd("Error: Map: not closed (hole - left)\n", 2), 0);
                if (grid[n.y][n.x + 1] == -1)
                    return (ft_putstr_fd("Error: Map: not closed (hole - right)\n", 2), 0);
			}
			n.x++;
		}
		n.y++;
	}
	return (11);
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
