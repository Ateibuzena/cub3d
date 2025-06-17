#include "../libft.h"

char	*ft_strclean(const char *str, char to_clean)
{
	int		i = 0;
	int		j = 0;
	char	*clean;

	if (!str)
		return (NULL);
	clean = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!clean)
		return (NULL);
	while (str[i])
	{
		if (str[i] != to_clean)
			clean[j++] = str[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}
