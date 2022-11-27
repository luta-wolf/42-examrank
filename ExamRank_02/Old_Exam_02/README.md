# Exam Rank 02
The first exam of the new cursus.

Subjects are in the folder of each exercises, along with a solution.

``get_next_line`` **passed** the Exam, and ``ft_printf`` didn't.

Проекты union и inter похожи.
Для того, чтобы при выводе избежать повторов создаем массив на 256 символов (по числу символов ACSII) и заполняем его нулями. При прохождении по строке меняем значение ячейки массива с номером равным номеру символа по таблице ACSII на 1. Чтобы char символа привести к его значению int используем приведение типов, (int)c.
Для лучшего понимания запустите этот код.

	#include <stdio.h>
	
	int main()
	{
		char *s = "Help";
		int i = 0;
		while(s[i])
		{
			printf("%c - %d\n", s[i], (int)s[i]);
			i++;
		}
	}
Получим символ и его значение ASCII:

	>$ ./a.out 
	H - 72
	e - 101
	l - 108
	p - 112
