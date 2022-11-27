int get_next_line(char **line)
{
   int       i;
   int       j;
   char   *buf;

   i = -1;
   buf = (char *)malloc(10000);
   j = read(0, &buf[++i], 1);
   while (j > 0 && buf[i] != '\n' && buf[i] != '\0')
      j = read(0, &buf[++i], 1);
   buf[i] = '\0';
   *line = buf;
   return (j);
}
