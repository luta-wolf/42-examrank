#include <unistd.h>
#include <stdarg.h>

//---------длина числа для d & x---------------
static int  ft_nbrlen(long n, int base_len) //base_len (10 - int or 16 - x)
{
	int i = 1;

	while (n >= base_len)
	{
		n /= base_len;
		i++;
	}
	return (i);
}
//----------из int в str -----------------------
static void ft_putnbr(long nbr, int base_len, char *base)
{
	if (nbr >= base_len) //base_len - 10, 16
		ft_putnbr(nbr / base_len, base_len, base);
	write(1, &base[nbr % base_len], 1);
}
//-----------------------------------------------------------------------------------------------------------------
int		ft_printf(const char *format, ...)
{
	va_list args;
	char	*str; // считываемая строка
	char	*s; // строка (s) из cspdiuxX
	long	nbr; // d и x из cspdiuxX
	int		neg; //флаг на минус
	int		len;//длина для проверок
	int		width; //ширина
	int		prec;//точность
	int		spaces;//пробел
	int		zeros;// ноль
	int		length; // возврашаемая длина

	va_start(args, format);
	str = (char *)format;
	length = 0;

	while (*str) // пока сушествует строка - идем по ней
	{
 		if (*str == '%') // если встречается
		{
            str++; // делаем шаг вперед
            neg = 0; //и инициализируем переменные
            len = 0;
            width = 0;
            prec = -1;
            spaces = 0;
            zeros = 0;
	//--------ширина-------------------------------
            while (*str >= '0' && *str <= '9') // если после % цифры
            {
                width = width * 10 + (*str - '0'); //перевожу в int
                str++;
            }
	//---------точность-----------------------------
            if (*str == '.') // если .
            {
                prec = 0; // это точность
                str++; //шаг вперед
                while (*str >= '0' && *str <= '9')
                {
                    prec = prec * 10 + (*str - '0'); //перевожу в int
        //25: prec = (0*10+ (2) ... 2*10+5 = 25 )
					str++; // шаг вперед
                }
            }
	//-----------s---------------------------------
            if (*str == 's') // если  s - это строка
            {
                s = va_arg(args, char *); // то это char *
                if (!s)
                    s = "(null)";
                while (s[len])
                    len++; // считываем строку
            }
	//-----------d---------------------------------
            if (*str == 'd') // если d - инт
            {
                nbr = va_arg(args, int); // то это int
                if (nbr < 0) // если отрицательное
                {
                    nbr = -nbr; //меняем - на +
                    neg = 1; // включаю флаг минуса
                }
                len = ft_nbrlen(nbr, 10) + neg; // длина числа + минус
            }
	//-----------x---------------------------------
            if (*str == 'x')
            {
                nbr = va_arg(args, unsigned); // то это unsigned
                len = ft_nbrlen(nbr, 16);
            }
	//-------------проверки-------------------------
			//----------точность--------------------
            if (prec >= len && *str != 's') // если точность больше длины и это не строка
                zeros = prec - len + neg;
            else if (prec < len && prec > -1 && *str == 's') // точность есть и точность меньше длины и это строка
                len = prec; // длина равна точности! приоритет точности
            else if (prec == 0 && (*str == 's' || nbr == 0)) // если точность  0 это строка или число 0, то  длина равна 0
                len = 0;
			//--------print " " "-" "0"-----------------------
            spaces = width - zeros - len;
            while (spaces-- > 0) //пока пробулы есть - вывожу
                length += write(1, " ", 1);
            if (neg == 1)//пишем "-" после пробелов
                write(1, "-", 1);
            while (zeros-- > 0)
                length += write(1, "0", 1);

			//--------печатать sdx -----------------
            if (*str == 's')
                write(1, s, len);
            else if (len > 0 && *str == 'd')
                ft_putnbr(nbr, 10, "0123456789");
            else if (len > 0 && *str == 'x')
                ft_putnbr(nbr, 16, "0123456789abcdef");
            length += len;
        }
        else // если нет %
            length += write(1, str, 1); // печатаю все и считаю
        str++;
    }
    va_end(args);
    return (length);
}
