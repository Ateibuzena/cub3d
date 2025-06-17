#include "../libft.h"

char	**ft_clean_double(char **original, char to_clean)
{
	char	**cleaned;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen_double(original);
	if (!original)
		return (NULL);
	cleaned = malloc((len + 1) * sizeof(char *));
	if (!cleaned)
		return (NULL);
	while (i < len)
	{
		cleaned[i] = ft_strclean(original[i], to_clean);
		if (!cleaned[i])
		{
			ft_freedouble(cleaned);
			return (NULL);
		}
		i++;
	}
	cleaned[len] = NULL;
	//ft_freedouble(original);
	return (cleaned);
}