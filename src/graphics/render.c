#include "../../include/cub3dft.h"

static int	ft_is_perspective_line_vertical(int x, int y,
				int point_x, int point_y, int spacing)
{
	double	dx;
	double	dy;
	double	offset;
	double	spacing_normalized;
	double	nearest_line;
	double	threshold;

	dx = x - point_x;
	dy = y - point_y;
	if (dy == 0)
		dy = 0.0001;
	offset = dx / dy;
	spacing_normalized = 1.0 / spacing;
	nearest_line = round(offset / spacing_normalized) * spacing_normalized;
	threshold = 0.01;
	return (fabs(offset - nearest_line) < threshold);
}

static int	ft_is_perspective_line_horizontal(int x, int y,
				int point_x, int point_y, int spacing, int floor_start)
{
	double	m;
	double	b;
	double	y_line_val;

	if (((y - floor_start) % spacing) >= 2)
		return (0);
	m = ((double)(y - point_y)) / (0 - point_x);
	b = point_y - m * point_x;
	y_line_val = m * x + b;
	return (fabs(y - y_line_val) < 2);
}

static void	ft_draw_ceiling(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, CEILING_COLOR);
			x++;
		}
		y++;
	}
}

static void	ft_draw_floor_with_perspective(t_game *game)
{
	int	y;
	int	x;
	int	point_x;
	int	point_y;
	int	line_spacing;
	int	color;

	y = HEIGHT / 2;
	point_x = WIDTH / 2;
	point_y = 0;
	line_spacing = 50;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = LINE_COLOR;
			if (ft_is_perspective_line_vertical(x, y, point_x,
					point_y, line_spacing)
				|| ft_is_perspective_line_horizontal(x, y, point_x,
					point_y, line_spacing, HEIGHT / 2))
				color = FLOOR_COLOR;
			mlx_put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_render_background(t_game *game)
{
	ft_draw_ceiling(game);
	ft_draw_floor_with_perspective(game);
}
