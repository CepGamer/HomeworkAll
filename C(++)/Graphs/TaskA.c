#include <stdio.h>

int main ()
{
  FILE *in, *out;
  int n, i, t;
  in = fopen("sortuniq.in", "r");
  out = fopen("sortuniq.out", "w");
  fscanf(in, "%d", &n);
  fprintf(out, "1");
  for(i = 2; i <= n; i++)
    fprintf(out, " %d", i);
  printf("\n");
  fclose(in);
  fclose(out);
  return 0;
}
