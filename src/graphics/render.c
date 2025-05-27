#include "../../include/cub3dft.h"

int	ft_floor_x(int x, int y, t_perspective *perspective)
{
	t_perspective_metrics metrics;

	metrics.dx = x - perspective->origin_x;
	metrics.dy = y - perspective->origin_y;
	if (metrics.dy == 0)
		metrics.dy = 0.0001;
	metrics.offset = metrics.dx / metrics.dy;
	metrics.spacing_normalized = 1.0 / perspective->spacing;
	metrics.nearest_line = round(metrics.offset / metrics.spacing_normalized) * metrics.spacing_normalized;
	metrics.threshold = 0.01;
	return (fabs(metrics.offset - metrics.nearest_line) < metrics.threshold);
}

int	ft_floor_y(int x, int y, t_perspective *perspective)
{
	double	m;
	double	y_intercept;
	double	line_y;

	if (((y - perspective->floor_start) % perspective->spacing) >= 2)
		return (0);
	m = ((double)(y - perspective->origin_y)) / (0 - perspective->origin_x);
	y_intercept = perspective->origin_y - m * perspective->origin_x;
	line_y = m * x + y_intercept;
	return (fabs(y - line_y) < 2);
}

void	ft_draw_ceiling(t_game *game)
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

void	ft_draw_floor(t_game *game)
{
	t_perspective		perspective;
	t_render_pixel		px;

	perspective.origin_x = WIDTH / 2;
	perspective.origin_y = 0;
	perspective.spacing = 48;
	perspective.floor_start = HEIGHT / 2;

	px.y = perspective.floor_start;
	while (px.y < HEIGHT)
	{
		px.x = 0;
		while (px.x < WIDTH)
		{
			px.color = LINE_COLOR;
			if (ft_floor_x(px.x, px.y, &perspective) || ft_floor_y(px.x, px.y, &perspective))
				px.color = FLOOR_COLOR;
			mlx_put_pixel(game->img, px.x, px.y, px.color);
			px.x++;
		}
		px.y++;
	}
}
