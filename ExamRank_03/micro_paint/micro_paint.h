#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int		sc_width;
	int		sc_height;
	char	ch;
	char	r;
	char	fill;
	float	x;
	float	y;
	float	width;
	float	height;
	FILE	*fp;
}	t_data;

#endif //EXAM_03_MICRO_PAINT_H
