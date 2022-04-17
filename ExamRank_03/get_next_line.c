// #include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	int rd = 0;
	char	c;
	if ((rd = read(fd, &c, 1)) == 0)
		return (NULL); // Возвращаем NULL, если файл пустой
	char	*line = malloc(100000); // 1000000 для BigFile1
	char	*word = line;
	*line++ = c;
	while ((rd = read(fd, &c, 1)) > 0 && c != '\n')
		*line++ = c;
	if (c == '\n')
		*line++ = '\n';
	*line = '\0';
	return (word);
}
/*
#include <stdio.h>

int main() // main1.c
{
	char *line;
	line = get_next_line(0);
	while (line != NULL)
	{

		printf("%s", line);
		free (line);
		line = get_next_line(0);
	}
	return (0);
}*/
