#include <unistd.h>

int main(int argc, char **argv)
{
   if (argc == 3)
   {
      char *s1 = argv[1];
      char *s2 = argv[2];
      int arr[256];
      int i = 0;
      while (i < 256)
      {
         arr[i] = 0;
         i++;
      }
      i = 0;
      while (s1[i])
      {
         if (arr[(int)s1[i]] == 0)
         {
            write(1, &s1[i], 1);
            arr[(int)s1[i]] = 1;
         }
         i++;
      }
      i = 0;
      while (s2[i])
      {
         if (arr[(int)s2[i]] == 0)
         {
            write(1, &s2[i], 1);
            arr[(int)s2[i]] = 1;
         }
         i++;
      }
   }
   write(1, "\n", 1);
}
