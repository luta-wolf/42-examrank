/*
Assignment name  : ft_strdup
Expected files   : ft_strdup.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Reproduce the behavior of the function strdup (man strdup).
Your function must be declared as follows:
char    *ft_strdup(char *src);

*/ 

// #include <stdlib.h>
// #include <stdio.h>

// char    *ft_strdup(char *src)
// {
//     int i = 0;
//     char *buffer;
    
//     while (src[i])
//     {
//         i++;
//     }
//     buffer = malloc(sizeof(char *) * (i + 1));
//     if (!buffer)
//         return NULL;
//     i = 0;
//     while (src[i])
//     {
//         buffer[i] = src[i];
//         i++;
//     }
//     buffer[i] = '\0';
//     return (buffer);
// }

// int main (void)
// {
//     char *str = "BAKYT 123";
//     printf("%s", ft_strdup(str));
//     return (0);
// }