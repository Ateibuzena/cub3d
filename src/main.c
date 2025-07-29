/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:33:16 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/29 16:29:33 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3dft.h"

static int	ft_check_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strcmp(path + len - 4, ".cub"))
		return (1);
	return (0);
}

static int	ft_check_args(char **argv)
{
	if (ft_atoi(argv[1]) != 0)
		return (0);
	if (!ft_check_extension(argv[1]))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !ft_check_args(argv))
		return (ft_putstr_fd("Error\n", 2), 1);
	ft_memset(&game, 0, sizeof(t_game));
	ft_init_game(&game, argv[1]);
	mlx_key_hook(game.mlx, (void *)ft_handle_key, &game);
	mlx_loop_hook(game.mlx, (void *)ft_handle_loop, &game);
	mlx_loop(game.mlx);
	ft_free_game(&game, NULL, NULL);
	ft_putstr_fd("\n[✅] Game terminated successfully\n", 1);
	return (0);
}
