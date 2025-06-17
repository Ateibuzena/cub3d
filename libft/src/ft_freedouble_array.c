#include "../libft.h"

void	ft_freedouble_array(int **array, int len)
{
	int		j;

	if (!array)
		return ;
	j = 0;
	while (j < len)
	{
		if (array[j])
		{
			free(array[j]);
			array[j] = 0;
		}
		j++;
	}
	free(array);
	array = 0;
}