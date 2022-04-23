#include <unistd.h>

int check(char c, int i, char *s)
{
   int j = 0;
   while (j < i)
   {
      if (s[j] == c)
         return 1;
      j++;
   }
   return 0;
}

int main(int argc, char **argv)
{
   if (argc == 3)
   {
      char *s1 = argv[1];
      char *s2 = argv[2];
      int i = 0;
      while (s1[i])
      {
         if (!check(s1[i], i, s1))
         {
            int j = 0;
            while (s2[j])
            {
               if (s1[i] == s2[j])
               {
                  write(1, &s1[i], 1);
                  break;
               }
               j++;
            }
         }
         i++;
      }
   }
   write(1, "\n", 1);
}
