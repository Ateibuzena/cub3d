#include "../include/cub3dft.h"

int	main(void)
{
	t_game	game;

	ft_init_window(&game);
	ft_load_textures(&game);
	ft_render_background(&game);
    ft_raycast(&game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}