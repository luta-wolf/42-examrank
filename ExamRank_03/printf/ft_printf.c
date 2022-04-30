#include <stdarg.h>
#include <unistd.h>

int  g_var = 0; //вводим глобальную переменную для подсчёта напечатанных симв-в

void ft_putnbr(long dig, int len, char *sign) // len для %d == 10
{
 if (dig >= len)
  ft_putnbr(dig/len, len, sign);
 write(1, &sign[dig % len], 1); // вывводим по символьно наши цифры
 g_var++; // увеличиваем кол-во напечатанных симв-в
}

void ft_puthex(unsigned dig, unsigned len, char *sign) //len для  %d == 16 / unsigned для сравнения с deg
{
 if (dig >= len)
  ft_puthex(dig/len, len, sign);
 write(1, &sign[dig % len], 1);
 g_var++;
}

int ft_printf(const char *format, ...)
{
 g_var = 0;
 va_list ap;
 va_start(ap, format);

 while (*format) // идем по строке
 {
  if (*format == '%') // если встречаем %, то ...
  {
   format++; // ... смотрим, какой спецификатор идёт после него
   if (*format == 's') // если спецификатор s, то ...
   {
    int len = 0;
    char *str = va_arg(ap, char *);
    if (!str)
     str = "(null)";
    while (str[len]) // считаем сколько символов нужно будет вывести
     len++;
    g_var += len; // присваиваем подсчитанное кол-во символов к глобальной переменной
    write(1, str, len); // выводим строку
   }
   else if (*format == 'd') // если же спецификатор d, то ...
   {
    long long d = va_arg(ap, int);
    if (d < 0) // если отрицательный, то ...
    {
     write(1, "-", 1); // выводим минус
     g_var++; // и увеличиваем кол-во выведенных символов на единицу
     d = -d; // ... меняем знак на противоположный
    }
    ft_putnbr(d, 10, "0123456789"); // ... отправляем на вывод
   }
   else if (*format == 'x') // если спецификатор x, то ...
   {
    int x = va_arg(ap, int);
    ft_puthex(x, 16, "0123456789abcdef"); // ... отправляем на вывод
   }
   format++; // переходим на следующий символ
  }
  else // если знака процента нет, то просто выводим по символьно текст
   g_var += write(1, format++, 1);
 }
 va_end(ap);
 return(g_var);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("I - %d\n", printf("qwerty %s\t%d\t%x\n", "stroka1", 2147148145, -42));
// 	printf("II - %d\n", ft_printf("qwerty %s\t%d\t%x\n", "stroka2", 2147148145, -42));
// 	return 0;
// }
