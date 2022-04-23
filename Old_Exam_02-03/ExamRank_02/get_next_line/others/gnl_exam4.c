#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//#include "get_next_line.h"

int		get_next_line(char **line)
{
	int readed;
	int i = 0;

	*line = malloc(1024 * 1024 * 4);
	if (!line)
		return (-1);
	while (((readed = read(0, *line + i, 1)) > 0))
	{
		if ((*line)[i] == '\n')
			break ;
		i++;
	}
	(*line)[i] = '\0';
	return (readed);
}

int main()
{
    char *line;
    printf("(%d) ",get_next_line(&line));
    printf("%s \n", line);
    return(0);
}
