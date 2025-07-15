/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:20:28 by azubieta          #+#    #+#             */
/*   Updated: 2025/07/10 12:34:22 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3dft.h"

static char	*ft_read_content(char *path)
{
	int		fd;
	char	*line;
	char	*content;
	char	*temp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: File: cannot open\n", 2), NULL);
	content = ft_strdup("");
	if (!content)
		return (close(fd), NULL);
	line = get_next_line(fd);
	while (line)
	{
		temp = content;
		content = ft_strjoin(content, line);
		free(temp);
		free(line);
		if (!content)
			return (close(fd), NULL);
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}

char	**ft_read_file(char *path)
{
	char	*content;
	char	**lines;

	content = ft_read_content(path);
	if (!content)
		return (NULL);
	if (ft_strlen(content) == 0)
	{
		free(content);
		return (ft_putstr_fd("Error: File: empty\n", 2), NULL);
	}
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		return (ft_putstr_fd("Error: File: failed to split content\n", 2), NULL);
	return (lines);
}
