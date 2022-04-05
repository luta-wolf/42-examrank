#include <stdarg.h>
#include <unistd.h>
int	g_var = 0;
void	ft_putnbr(long dig, int len, char *sign) {
	if (dig >= len)
		ft_putnbr(dig/len, len, sign);
	write (1, &sign[dig % len], 1);
	g_var++;
}
int	ft_printf(const char *fmt, ...) {
	va_list	ap;
	va_start(ap, fmt);
	while (*fmt) {
		if (*fmt == '%') {
			fmt++;
			if (*fmt == 's') {
				int	len = 0;
				char *str = va_arg(ap, char *);
				if (!str)
					str = "(null)";
				while (str[len])
					len++;
				g_var += len;
				write(1, str, len);
			}
			else if (*fmt == 'd') {
				int d = va_arg(ap, int);
				if (d < 0) {
					write(1, "-", 1);
					g_var++;
					d = -d;
				}
				ft_putnbr(d, 10, "0123456789");
			}
			else if (*fmt == 'x') {
				int x = va_arg(ap, unsigned);
				ft_putnbr(x, 16, "0123456789abcdef");
			}
			fmt++;
		}
		else
			g_var += write(1, fmt++, 1);
	}
	va_end(ap);
	return(g_var);
}
