/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:46:40 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/22 22:35:33 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

// (0.0 a 1.0)
unsigned int	ft_desaturate(unsigned int color, float factor)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}

unsigned int	ft_invert_color(unsigned int color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = 255 - ((color >> 16) & 0xFF);
	g = 255 - ((color >> 8) & 0xFF);
	b = 255 - (color & 0xFF);
	return ((r << 16) | (g << 8) | b);
}
