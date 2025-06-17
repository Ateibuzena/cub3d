#include "../../include/cub3dft.h"

static int	ft_compute_y(int area)
{
	int	origin_y;

	origin_y = 0;
	if (area == BG_FLOOR)
		origin_y = VANISH_Y;
	else if (area == BG_CEILING)
		origin_y = VANISH_Y - 1;
	return (origin_y);
}

static int	ft_is_radial_line(int x, int y, t_background *ctx)
{
	double	dx;
	double	dy;
	double	offset;
	double	nearest_line;
	double	spacing_norm;
	double	threshold;

	dx = x - ctx->origin_x;
	dy = y - ctx->origin_y;
	if (dy == 0)
		dy = (ctx->area == BG_FLOOR) ? 0.0001 : -0.0001;
	offset = dx / dy;
	spacing_norm = 10.0 / GRID_SPACING;
	nearest_line = round(offset / spacing_norm) * spacing_norm;
	threshold = 0.0008;
	return (fabs(offset - nearest_line) < threshold);
}

static int	ft_is_horizontal_line(int x, int y, t_background *ctx)
{
	double	dy;

	(void)x;
	dy = y - ctx->origin_y;
	return (((int)fabs(dy)) % GRID_SPACING < 1);
}

static void	ft_draw_pixel_if_line(int x, int y, t_background *ctx, t_game *game)
{
	if (ft_is_radial_line(x, y, ctx) || ft_is_horizontal_line(x, y, ctx))
		mlx_put_pixel(game->img, x, y, ctx->color);
}

static void	ft_draw_grid_area(t_game *game, t_background *ctx)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_draw_pixel_if_line(x, y, ctx, game);
			x++;
		}
		y++;
	}
}

void	ft_draw_background(t_game *game, int area)
{
	t_background	ctx;

	if (area == BG_NONE)
		return ;
	ctx.origin_x = WIDTH / 2;
	ctx.origin_y = ft_compute_y(area);
	ctx.area = area;
	ctx.color = (area == BG_FLOOR) ? LINE_FLOOR : LINE_CEILING;
	ft_draw_grid_area(game, &ctx);
}
