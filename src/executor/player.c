#include "../../include/cub3dft.h"

void ft_rotate_player(t_game *game)
{
    float angle_speed = (0.1);

    if (game->player.left_rotate)
        game->player.angle -= angle_speed;
    if (game->player.right_rotate)
        game->player.angle += angle_speed;

    if (game->player.angle > 2 * M_PI)
        game->player.angle -= 2 * M_PI;
    if (game->player.angle < 0)
        game->player.angle += 2 * M_PI;
}

bool    ft_touch(float px, float py, t_game *game)
{
	int cell_x = (int)(px / TILE_SIZE);
	int cell_y = (int)(py / TILE_SIZE);

	return (game->map.grid[cell_y][cell_x] == 0);
}

static bool ft_can_move_to(float x, float y, t_game *game)
{
	return (
		ft_touch(x - PLAYER_RADIUS, y - PLAYER_RADIUS, game) &&  // arriba izquierda
		ft_touch(x + PLAYER_RADIUS, y - PLAYER_RADIUS, game) &&  // arriba derecha
		ft_touch(x - PLAYER_RADIUS, y + PLAYER_RADIUS, game) &&  // abajo izquierda
		ft_touch(x + PLAYER_RADIUS, y + PLAYER_RADIUS, game)     // abajo derecha
	);
}

void ft_move_direction(t_game *game, float dx, float dy)
{
    float new_x = game->player.x + dx;
    float new_y = game->player.y + dy;

    // Movimiento horizontal independiente
    if (ft_can_move_to(new_x, game->player.y, game))
        game->player.x = new_x;

    // Movimiento vertical independiente
    if (ft_can_move_to(game->player.x, new_y, game))
        game->player.y = new_y;
}

void ft_move_player(t_game *game)
{
    float speed = (TILE_SIZE * 0.2);
    float cos_angle = cos(game->player.angle);
    float sin_angle = sin(game->player.angle);

    ft_rotate_player(game);

    if (game->player.key_up)
        ft_move_direction(game, cos_angle * speed, sin_angle * speed);
    if (game->player.key_down)
        ft_move_direction(game, -cos_angle * speed, -sin_angle * speed);
    if (game->player.key_left)
        ft_move_direction(game, sin_angle * speed, -cos_angle * speed);
    if (game->player.key_right)
        ft_move_direction(game, -sin_angle * speed, cos_angle * speed);
    
}
