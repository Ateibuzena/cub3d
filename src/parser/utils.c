#include "../../include/cub3dft.h"

int	ft_strlen_nospace(char *str)
{
	int i = 0;
	int count = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			count++;
		i++;
	}
	return (count);
}

void	ft_free_textures(t_game *game)
{
	if (game->textures.north)
		mlx_delete_texture(game->textures.north);
	if (game->textures.south)
		mlx_delete_texture(game->textures.south);
	if (game->textures.east)
		mlx_delete_texture(game->textures.east);
	if (game->textures.west)
		mlx_delete_texture(game->textures.west);
}

void	ft_free_paths(t_data *data)
{
	if (data->paths.north)
		free(data->paths.north);
	if (data->paths.south)
		free(data->paths.south);
	if (data->paths.east)
		free(data->paths.east);
	if (data->paths.west)
		free(data->paths.west);
}