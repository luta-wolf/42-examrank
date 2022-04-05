/*
Assignment name  : pgcd
Expected files   : pgcd.c
Allowed functions: printf, atoi, malloc, free
--------------------------------------------------------------------------------

Write a program that takes two strings representing two strictly positive
integers that fit in an int.

Display their highest common denominator followed by a newline (It's always a
strictly positive integer).

If the number of parameters is not 2, display a newline.

Examples:

$> ./pgcd 42 10 | cat -e
2$
$> ./pgcd 42 12 | cat -e
6$
$> ./pgcd 14 77 | cat -e
7$
$> ./pgcd 17 3 | cat -e 
1$
$> ./pgcd | cat -e
$
*/

/*
#include <stdlib.h>
#include <stdio.h>


void    ft_pdgc(char *str1, char *str2)
{
    int i = atoi(str1);
    int j = atoi(str2);
    int den = 1;

    if (i < 0 || j < 0)
        return ;
    if (i > j)
        den = j;
    else
        den = i;
    while (den > 0)
    {
        if (i % den == 0 && j % den == 0)
            {
                printf("%d", den);
                break;
            }
        den--;
    }
    return ;
}

int    main(int argc, char **argv)
{
    if (argc == 3)
        ft_pdgc(argv[1], argv[2]);
    printf("\n");
    return (0);
}
*/