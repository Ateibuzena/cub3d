#include "../../include/cub3dft.h"

char **ft_read_file(char *path)
{
    int     fd;
    char    *line;
    char    *content;
    char    **lines;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Error: Cannot open file\n", 2), NULL);
    content = NULL;
    while ((line = get_next_line(fd)))
    {
        char *temp;

        temp = content;
        content = ft_strjoin(content, line);
        free(temp);
        free(line);
    }
    close(fd);
    lines = ft_split(content, '\n');
    free(content);
    return (lines);
}
