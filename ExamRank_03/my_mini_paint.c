#include <unistd.h>
#include <stdio.h>

int ft_exit(FILE *file, char *map)
{
	if (file)
		fclose(file);
	if (map)
		free(map);
	write(1, "Error: Operation file corrupted\n", 32);

	return 1;
}

int main(int argc, char **argv)
{
	FILE	*file = NULL;
	char	*map = NULL;
	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (1);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
		return(ft_exit(file, map));
	fclose(file);
	return 0;
}
