#include "mini_paint.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	parser(char **argv, t_data *data)
{
	int	c;

	data->fp = fopen(argv[1], "r");
	if (data->fp == NULL) // если файл не открылся или неверный путь
	{
		error("Error: Operation file corrupted\n");
		return (1);
	}
	c = fscanf(data->fp, "%d %d %c\n", &data->sc_width, &data->sc_height,
			   &data->ch); // читаем ширину, высоту и символ поля. Возвращает
			   // количество верно считанных переменных
   if (c <= 0 || c != 3) // если есть ошибки, неверный тип и тд
	{
		error("Error: Operation file corrupted\n");
		return (1);
	}
   if ((data->sc_height > 300 || data->sc_height <= 0) || (data->sc_width > 300
   		|| data->sc_width <= 0)) // если заданы неверно границы поля
   {
		error("Error: Operation file corrupted\n");
		return (1);
	}
   return (0);
}


void	free_func(t_data *data, char **arr)
{
	int	i;

	i = 0;
	while (i < data->sc_height)
		free(arr[i++]);
	free(arr);
	fclose(data->fp);
}

void	full_matrix(t_data *data, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->sc_height)
	{
		j = 0;
		while (j < data->sc_width)
		{
			arr[i][j] = data->ch;
			j++;
		}
		i++;
	}
}

void	print_res(t_data *data, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->sc_height)
	{
		j = 0;
		while (j < data->sc_width)
		{
			write(1, &arr[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

float	find_pixel(t_data *data, float x_0, float y_0)
{
	return (sqrtf((data->x - x_0) * (data->x - x_0) + (data->y - y_0) *
		(data->y-y_0)));
}

void draw_full_circle(t_data *data, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->sc_height)
	{
		j = 0;
		while (j < data->sc_width)
		{
			if (data->radius >= find_pixel(data, j ,i))
				arr[i][j] = data->fill;
			j++;
		}
		i++;
	}
}

void draw_empty_circle(t_data *data, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->sc_height)
	{
		j = 0;
		while (j < data->sc_width)
		{
			if (data->radius - 1 > find_pixel(data, j ,i))
				arr[i][j] = arr[i][j];
			else if (data->radius >= find_pixel(data, j ,i))
				arr[i][j] = data->fill;
			j++;
		}
		i++;
	}
}

int	general_func(char **argv)
{
	t_data	data;
	char	**arr;
	int		i;
	int		c;

	if (parser(argv, &data))
	{
		fclose(data.fp);
		return (1);
	}
	arr = (char **)malloc((data.sc_height + 1) * sizeof(char *));
	i = 0;
	while (i < data.sc_height)
		arr[i++] = (char *)malloc((data.sc_width + 1) * sizeof(char));
	full_matrix(&data, arr); // заполнение всей матрицы символом поля
	while ((c = fscanf(data.fp, "%c %f %f %f %c\n", &data.c, &data.x,
					   &data.y, &data.radius, &data.fill)) == 5)
	{
		if ((data.c != 'c' && data.c != 'C') || data.radius <= 0)
		{
			error("Error: Operation file corrupted\n");
			free_func(&data, arr);
			return (1);
		}
		if (data.c == 'C')
			draw_full_circle(&data, arr); // заполненный внутри символами круг
		if (data.c == 'c')
			draw_empty_circle(&data, arr); // только граница круга
	}
	if (c != -1) // ошибка в файле с параметрами, -1 - достигнут конец файла
	{
		error("Error: Operation file corrupted\n");
		free_func(&data, arr);
		return (1);
	}
	print_res(&data, arr);
	free_func(&data, arr);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (general_func(argv))
			return (1);
	}
	else
	{
		write(1, "Error: argument\n", ft_strlen("Error: argument\n"));
		return (1);
	}
	return (0);
}
