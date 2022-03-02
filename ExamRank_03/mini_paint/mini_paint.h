#ifndef MINI_PAINT_H
# define MINI_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef struct s_data
{
	int		sc_width;
	int		sc_height;
	char	ch;
	char	c;
	char	fill;
	float	x;
	float	y;
	float 	radius;
	FILE	*fp;
}	t_data;

#endif //EXAM_03_MINI_PAINT_H