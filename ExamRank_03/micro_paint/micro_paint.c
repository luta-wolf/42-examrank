#include "micro_paint.h"

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

void	draw_empty_rec(t_data *data, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->sc_height)
	{
		j = 0;
		while (j < data->sc_width)
		{
			if ((float)i >= data->y + 1 && (float)j >= data->x + 1 && (
					(float)i <= data->height + data->y - 1) && ((float)j
					<= data->width + data->x - 1))
				arr[i][j] = arr[i][j];
			else if (((float)i >= data->y) && ((float)j >= data->x) && (
					(float)i <= data->height + data->y) && ((float)j
					<= data->width + data->x))
				arr[i][j] = data->fill;
			j++;
		}
		i++;
	}
}

void	draw_full_rec(t_data *data, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->sc_height)
	{
		j = 0;
		while (j < data->sc_width)
		{
			if (((float)i >= data->y) && ((float)j >= data->x) && ((float)i
					<= data->height + data->y) && ((float)j
					<= data->width + data->x))
				arr[i][j] = data->fill;
			j++;
		}
		i++;
	}
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
	while ((c = fscanf(data.fp, "%c %f %f %f %f %c\n", &data.r, &data.x,
				  &data.y, &data.width, &data.height, &data.fill)) == 6)
	{
		if ((data.r != 'r' && data.r != 'R') || data.width <= 0
			|| data.height <= 0)
		{
			error("Error: Operation file corrupted\n");
			free_func(&data, arr);
			return (1);
		}
		if (data.r == 'R')
			draw_full_rec(&data, arr); // заполненный внутри символами прямоугольник
		if (data.r == 'r')
			draw_empty_rec(&data, arr); // только граница прямоугольника
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
