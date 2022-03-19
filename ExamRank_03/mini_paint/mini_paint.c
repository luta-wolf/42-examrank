#include <stdio.h>
#include <unistd.h>
#include <math.h>
int ft_error(FILE *file)
{
	write(1, "Error: Operation file corrupted\n", 32);
	fclose(file);
	return 1;
}
int main(int argc, char **argv)
{
	FILE *file;
	int i =-1, j, height, width, arg;
	float x, y, radius, res;
	char back, c, symb;
	if(argc != 2)
		return(write(1, "Error: argument\n", 16) && 1);
	if(!(file = fopen(argv[1], "r")))
		return(write(1, "Error: Operation file corrupted\n", 32) && 1);
	if((arg = fscanf(file, "%d %d %c\n", &width, &height, &back)) != 3)
		return(ft_error(file));
	if(height <= 0 || height > 300 || width <=0 || width > 300)
		return(ft_error(file));
	char arr[height][width];
	while(++i < height)
	{
		j = -1;
		while(++j < width)
			arr[i][j] = back;
	}
	while((arg = fscanf(file, "%c %f %f %f %c\n", &c, &x, &y, &radius, &symb)) == 5)
	{
		if((c != 'c' && c != 'C') || radius <= 0)
			return(ft_error(file));
		i = -1;
		while(++i < height)
		{
			j = -1;
			while(++j < width)
			{
				res = sqrt(pow(i - y, 2) + pow(j - x, 2));
				if(res <= radius)
					if((radius - res < 1 && c == 'c') || c == 'C')
						arr[i][j] = symb;
			}
		}
	}
	if(arg > 0 && arg !=5)
		return(ft_error(file));
	i = -1;
	while(++i < height)
	{
		j = -1;
		while(++j < width)
			write(1, &arr[i][j], 1);
		write(1, "\n", 1);
	}
	return(fclose(file) && 0);
}
