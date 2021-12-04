#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int get_next_line(char **line)
{
    int i = 0,j;
    char *buf;
    buf = (char *)malloc(10000);
    while((j = read(0, &buf[i], 1)) == 1 && buf[i] != '\n' && buf[i] != '\0')
        i++;
    buf[i] = '\0';
    *line = buf;
    return(j);
}
