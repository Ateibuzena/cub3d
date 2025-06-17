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
        content = ft_strjoin(content, line); // strjoin + free primero
        free(temp);
        free(line);
    }
    close(fd);
    lines = ft_split(content, '\n');
    free(content);
    return (lines);
}

/*char    **ft_read_file(char *path)
{
    char    **result = NULL;
    int     fd;
    char    *line;
    int     count = 0;
    t_list  *lines;
    t_list  *temp;
    int     i;

    i = 0;
    count = 0;
    lines = NULL;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    line = get_next_line(fd);
    while (line)
    {
        t_list *node = ft_lstnew(ft_strdup(line));
        free(line);
        ft_lstadd_back(&lines, node);
        line = get_next_line(fd);
        count++;
    }
    close(fd);
    result = malloc(sizeof(char *) * (count + 1));
    if (!result)
        return (NULL);
    while (lines)
    {
        result[i++] = lines->content;
        temp = lines;
        lines = lines->next;
        free(temp);
    }
    result[i] = NULL;
    return (result);
}*/
