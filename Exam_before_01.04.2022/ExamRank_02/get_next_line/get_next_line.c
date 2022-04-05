#include <unistd.h>
#include <stdlib.h>

int get_next_line(char **line)
{
	int i = 0;
	int rd;

	*line = (char *)malloc(1000);
	while((rd = read(0, *line + i, 1)) > 0)
	{
		if((*line)[i] == '\n')
			break;
		i++;
	}
	(*line)[i] = '\0';
	return rd;
}

