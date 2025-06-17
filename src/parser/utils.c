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
