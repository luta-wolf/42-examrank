#include <stdio.h>

int	ft_printf(char const *format, ...);

#ifndef FLAG
#define P	ret += ft_printf
#else
#define P	ret += printf
#endif

int	main(void)
{
	int	ret;
	int r;

	r = 0;
	P("\n");
	P("%d", 0);
	P("%d", 42);
	P("%d", 1);
	P("%d", 5454);
	P("%d", (int)2147483647);
	P("%d", (int)2147483648);
	P("%d", (int)-2147483648);
	P("%d", (int)-2147483649);
	P("\n");
	P("%x", 0);
	P("%x", 42);
	P("%x", 1);
	P("%x", 5454);
	P("%x", (int)2147483647);
	P("%x", (int)2147483648);
	P("%x", (int)-2147483648);
	P("%x", (int)-2147483649);
	P("%s", "");
	P("%s", "toto");
	P("%s", "wiurwuyrhwrywuier");
	P("%s", NULL);
	P("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	P("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	P("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	P("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	P("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	printf("written: %d\n", ret);
}
