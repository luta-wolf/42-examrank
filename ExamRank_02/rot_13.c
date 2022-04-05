/* 

Assignment name  : rot_13
Expected files   : rot_13.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it, replacing each of its
letters by the letter 13 spaces ahead in alphabetical order.

'z' becomes 'm' and 'Z' becomes 'M'. Case remains unaffected.

The output will be followed by a newline.

If the number of arguments is not 1, the program displays a newline.

Example:

$>./rot_13 "abc"
nop
$>./rot_13 "My horse is Amazing." | cat -e
Zl ubefr vf Nznmvat.$
$>./rot_13 "AkjhZ zLKIJz , 23y " | cat -e
NxwuM mYXVWm , 23l $
$>./rot_13 | cat -e
$
$>
$>./rot_13 "" | cat -e
$
$>
*/

// #include <unistd.h>

// void    ft_rot13(char *str)
// {
//     int i = 0;
//     int t;
//     char    ch;

//     while (str[i])
//     {
//         t = 0;
//         ch = str[i];
//         if (ch >= 'a' && ch <= 'm')
//         {
//             ch = ch + 13;
//             write(1, &ch, 1); 
//         }
//         else if (ch >= 'A' && ch <= 'M')
//         {
//             ch = ch + 13;
//             write(1, &ch, 1); 
//         }
//         else if (ch >= 'n' && ch <= 'z')
//         {
//             t = 'z' - ch;
//             ch = 'a' + 12 - t;
//             write(1, &ch, 1); 
//         }
//         else if (ch >= 'N' && ch <= 'Z')
//         {
//             t = 'Z' - ch;
//             ch = 'A' + 12 - t;
//             write(1, &ch, 1); 
//         }
//         else 
//             write(1, &ch, 1); 
//         i++;
//     }
// }

// int    main(int argc, char **argv)
// {
//     if (argc == 2)
//         ft_rot13(argv[1]);
//     write(1, "\n", 1);
//     return (0);
// }

