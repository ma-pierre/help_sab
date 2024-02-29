#include "../minishell.h"

#define BUFFER_SIZE 1

char    *fill_line(char **buffer)
{
    char    *line;
    char    *updated_buffer;
    int     i;

    line = NULL;
    updated_buffer = NULL;
    i = 0;
	if (!(*buffer && **buffer))
		return (NULL);
    while ((*buffer)[i] && (*buffer)[i] != '\n')
        i++;
    if((*buffer)[i] == '\n') 
    {
        updated_buffer = ft_strdup((*buffer) + i + 1);
        if(!updated_buffer)
            return(NULL);
        (*buffer)[i + 1] = '\0';
        line = ft_strdup(*buffer);
        if(!line)
            return(NULL);
        free(*buffer);
        *buffer = updated_buffer;
    }
    else if((*buffer)[i] == '\0')
    {
        line = ft_strdup(*buffer);
        if(!line)
            return(NULL);
        free(*buffer);
        *buffer = NULL;
    }
    return(line);
}

char    *get_next_line(int fd)
{
    static char *buffer;
    char        *temp;
    char        *line;
    int         byte_rd;

    byte_rd = 0;
    if(fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
    temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!temp)
        return(NULL);
    while(!ft_strchr(buffer, '\n'))
    {
        byte_rd = read(fd, temp, BUFFER_SIZE);
        if(byte_rd <= 0)
            break;
        temp[byte_rd] = '\0';
        if (!buffer)
            buffer = ft_strdup(temp);
        else
            buffer = ft_strjoin(buffer, temp);
        if (buffer == NULL)
            return(NULL);
    }
    free(temp);
    line = fill_line(&buffer);
    if(!line)
    {
        free(buffer);
        buffer = NULL;
    }
    return(line);
}

/*int main(int argc, char **argv)
{
    int fd;
    char *line;
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        line = get_next_line(fd);
        printf("%s", line);
        while (line)
        {
            if (line)
                free(line);
            line = get_next_line(fd);
            printf("%s", line);            
        }
        if(line)
            free(line);
        close(fd);
    }
    return(0);
}*/