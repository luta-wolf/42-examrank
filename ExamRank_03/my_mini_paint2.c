#include <unistd.h>

int main(int ac, char av)
{
	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}

}
