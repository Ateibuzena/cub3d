#include "../../include/cub3dft.h"

void ft_key_press(t_game *game, int key)
{
    if (key == MLX_KEY_W)
        game->player.key_up = true;
    else if (key == MLX_KEY_S)
        game->player.key_down = true;
    else if (key == MLX_KEY_A)
        game->player.key_left = true;
    else if (key == MLX_KEY_D)
        game->player.key_right = true;
    else if (key == MLX_KEY_LEFT)
        game->player.left_rotate = true;
    else if (key == MLX_KEY_RIGHT)
        game->player.right_rotate = true;
    else if (key == MLX_KEY_ESCAPE)
    {
        mlx_close_window(game->mlx);
        mlx_terminate(game->mlx);
        exit(EXIT_SUCCESS);
    }
}

void ft_key_release(t_game *game, int key)
{
    if (key == MLX_KEY_W)
        game->player.key_up = false;
    else if (key == MLX_KEY_S)
        game->player.key_down = false;
    else if (key == MLX_KEY_A)
        game->player.key_left = false;
    else if (key == MLX_KEY_D)
        game->player.key_right = false;
    else if (key == MLX_KEY_LEFT)
        game->player.left_rotate = false;
    else if (key == MLX_KEY_RIGHT)
        game->player.right_rotate = false;
}

void ft_handle_key(mlx_key_data_t keydata, void *param)
{
    t_game   *game;

    game = (t_game *)param;
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
        ft_key_press(game, keydata.key);
    else if (keydata.action == MLX_RELEASE)
        ft_key_release(game, keydata.key);
}

int	ft_handle_loop(t_game *game)
{
	ft_move_player(game);
	ft_clear_image(game);
	
    //ft_draw_background(game, BG_FLOOR);  // líneas en el suelo
    //ft_draw_background(game, BG_CEILING);  // líneas en el suelo
	int	i;
	float camera_x;
	float ray_angle;

	i = 0;
	while (i < WIDTH)
	{
		camera_x = 2 * i / (float)WIDTH - 1; // de -1 a 1
		ray_angle = game->player.angle + atan(camera_x * tan(FOV / 2));
		ft_render_wall(game, ray_angle, i);
		i++;
	}
	return (0);
}
