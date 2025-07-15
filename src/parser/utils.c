/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/15 14:22:07 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

int	ft_strlen_nospace(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			count++;
		i++;
	}
	return (count);
}

int	ft_map_start(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ' || lines[i][j] == '\t')
			j++;
		if (lines[i][j] == '1' || lines[i][j] == '0')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_map_dimensions(char **lines, int start, t_data *data)
{
	int	i;
	int	max_width;
	int	len;

	i = start;
	max_width = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	data->map.height = i - start;
	data->map.width = max_width;
}

mlx_texture_t	*ft_load_png(const char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_putstr_fd("Error: Texture: failed to load PNG: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	return (texture);
}

mlx_texture_t	*ft_load_xpm(const char *path, xpm_t **xpm_storage)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42(path);
	if (!xpm)
	{
		ft_putstr_fd("Error: Textures: failed to load XPM: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	*xpm_storage = xpm;
	return (&xpm->texture);
}
