/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:33:16 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/17 11:57:46 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3dft.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	ft_init_game(&game, argv[1]);
	mlx_key_hook(game.mlx, (void *)ft_handle_key, &game);
	mlx_loop_hook(game.mlx, (void *)ft_handle_loop, &game);
	mlx_loop(game.mlx);
	ft_free_game(&game, NULL, NULL);
	ft_putstr_fd("\n[✅] Game terminated successfully\n", 1);
	return (0);
}
