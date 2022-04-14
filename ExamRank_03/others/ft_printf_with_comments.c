#include <stdarg.h>
#include <unistd.h>
int	g_var = 0;	//глобальная переменная для подсчета напечатанных символов
void	ft_putnbr(long dig, int len, char *sign) { //len: для %d == 10 для %x == 16
	if (dig >= len)
		ft_putnbr(dig/len, len, sign);
	write (1, &sign[dig % len], 1); //выводим по символьно нашы цифры
	g_var++; // увеличивая кол-во напечатанных символов
}
int	ft_printf(const char *fmt, ...) {
	va_list	ap;
	va_start(ap, fmt);
	while (*fmt) { //идем по строке пока не закончится
		if (*fmt == '%') { // если встречаем процент, то...
			fmt++; //...смотрим какой спецификатор стоит после него
			if (*fmt == 's') { //если спецификатора s
				int	len = 0;
				char *str = va_arg(ap, char *);
				if (!str)
					str = "(null)";
				while (str[len]) //считаем сколько символов нужно будет выведенно
					len++;
				g_var += len; //присваиваем подсчитанное кол-во символов к глобальной переменной
				write(1, str, len); //выводим строку
			}
			else if (*fmt == 'd') { //если спецификатор d
				int d = va_arg(ap, int);
				if (d < 0) { //если отрицательный, то...
					write(1, "-", 1); //выводим минус
					g_var++; // и увиличиваем кол-во выведенных символов на единицу
					d = -d;//...меняем знак на противоположный
				}
				ft_putnbr(d, 10, "0123456789");
			}
			else if (*fmt == 'x') { // если спецификатор х
				int x = va_arg(ap, unsigned);
				ft_putnbr(x, 16, "0123456789abcdef"); //отправляем на вывод
			}
			fmt++; //переходим на следующий символ
		}
		else // если знака процента нет то просто выводим по символьно текст
			g_var += write(1, fmt++, 1);
	}
	va_end(ap);
	return(g_var);
}
