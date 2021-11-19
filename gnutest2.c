#include <math.h>
#include <stdio.h>
#define NX 720
int main(void) {
  FILE *data, *gp;
  char *data_file;
  int i;
  double dx, x, y;
  /*------ データファイル作成 ---------- */
  data_file = "out.dat";
  data = fopen(data_file, "w");
  dx = 4 * M_PI / NX;
  for (i = 0; i <= NX; i++) {
    x = -2 * M_PI + i * dx;
    y = sin(x);
    fprintf(data, "%f\t%f\n", x, y);
  }
  fclose(data);
  /*------ グラフの作成 ---------- */
  gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set xrange [-6.5:6.5]\n");
  fprintf(gp, "set yrange [-1.5:1.5]\n");
  fprintf(gp, "plot \"%s\" with lines linetype 1 title \"sin\"\n", data_file);
  pclose(gp);
  return 0;
}