#include "../../include/cub3dft.h"

static int	ft_is_perspective_line_vertical(int x, int y,
				int point_x, int point_y, int spacing)
{
	t_perspective_calc p;

	p.dx = x - point_x;
	p.dy = y - point_y;
	if (p.dy == 0)
		p.dy = 0.0001;
	p.offset = p.dx / p.dy;
	p.spacing_normalized = 1.0 / spacing;
	p.nearest_line = round(p.offset / p.spacing_normalized) * p.spacing_normalized;
	p.threshold = 0.01;
	return (fabs(p.offset - p.nearest_line) < p.threshold);
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
	t_perspective_params p;

	p.y = HEIGHT / 2;
	p.point_x = WIDTH / 2;
	p.point_y = 0;
	p.line_spacing = 48;
	while (p.y < HEIGHT)
	{
		p.x = 0;
		while (p.x < WIDTH)
		{
			p.color = LINE_COLOR;
			if (ft_is_perspective_line_vertical(p.x, p.y, p.point_x,
					p.point_y, p.line_spacing)
				|| ft_is_perspective_line_horizontal(p.x, p.y, p.point_x,
					p.point_y, p.line_spacing, HEIGHT / 2))
				p.color = FLOOR_COLOR;
			mlx_put_pixel(game->img, p.x, p.y, p.color);
			p.x++;
		}
		p.y++;
	}
}

void	ft_render_background(t_game *game)
{
	ft_draw_ceiling(game);
	ft_draw_floor_with_perspective(game);
}
