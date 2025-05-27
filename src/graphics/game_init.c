#include "../../include/cub3dft.h"

void	ft_init_game(t_game *game)
{
	ft_init_mlx(game);
	ft_init_player(game);
	ft_init_map(game);
	ft_fill_grid(game);
	ft_load_textures(game);
}
