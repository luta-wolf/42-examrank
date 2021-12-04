#include <unistd.h>

int check(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	int i;
	int j;
	char s[256];

	i = 0;
	j = 0;
	if (argc == 3)
	{
		while (argv[1][i]) {
			if (check(s, argv[1][i])) {
				s[j] = argv[1][i];
				write(1, &argv[1][i], 1);
				j++;
			}
			i++;
		}
		i = 0;
		while (argv[2][i]) {
			if (check(s, argv[2][i])) {
				s[j] = argv[2][i];
				write(1, &argv[2][i], 1);
				j++;
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}
