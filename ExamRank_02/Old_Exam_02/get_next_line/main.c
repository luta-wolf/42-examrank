#include <stdio.h>
int get_next_line(char **line);

int main()
{
	char *line;
	printf("(%d) ", get_next_line(&line));
	printf("%s \n", line);
	return (0);
}
