/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:23:31 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/16 14:54:28 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned int		len;
	char				*ptr;

	ptr = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	c = (unsigned char)c;
	while (len)
	{
		if (str[len] == c)
		{
			ptr = (char *)str + len;
			return (ptr);
		}
		len--;
	}
	if (c == '\0')
		ptr = (char *)str + ft_strlen(str);
	return (ptr);
}
